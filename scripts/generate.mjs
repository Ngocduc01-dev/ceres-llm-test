#!/usr/bin/env node
// Phase 5 – gửi units/<id>/prompt.md cho Claude (qua Claude Code CLI), lưu câu trả lời và file test.
//
//   units/<id>/response.md   – nguyên văn câu trả lời (bảng CFG, nhánh, test path, test case, C2 dự kiến)
//   units/<id>/<id>_test.cc  – khối code có dòng "// FILE:" tách từ câu trả lời
//
// Gọi được đến đâu lưu đến đó: unit đã có response.md thì bỏ qua; gặp lỗi đăng nhập / hết lượt dùng thì dừng.
//
// Chạy trên máy đã đăng nhập Claude Code CLI (`claude`, rồi `/login`):
//   node scripts/generate.mjs --smoke              # 20 unit smoke test
//   node scripts/generate.mjs --limit 50           # 50 unit tiếp theo (theo topo_level)
//   node scripts/generate.mjs --ids u0553 u0502
//   node scripts/generate.mjs --smoke --dry-run    # chỉ in ra sẽ gọi unit nào
//   node scripts/generate.mjs --force --ids u0553  # gọi lại dù đã có response.md
import { spawn } from "node:child_process";
import { appendFileSync, existsSync, mkdirSync, readFileSync, writeFileSync } from "node:fs";
import { dirname, join } from "node:path";
import { fileURLToPath } from "node:url";

const REPO = join(dirname(fileURLToPath(import.meta.url)), "..");
const MODEL = "claude-sonnet-5-5";
const SYSTEM = "Bạn là kỹ sư kiểm thử phần mềm C++. Làm đúng theo yêu cầu trong tin nhắn.";
const EFFORT = "low";
const TIMEOUT_MS = 15 * 60 * 1000;
const STOP_PATTERNS = /auth|login|oauth|rate.?limit|usage limit|quota|credit|overloaded|session expired/i;

// ---- tham số
const argv = process.argv.slice(2);
const flag = (f) => argv.includes(f);
const listAfter = (f) => {
  const i = argv.indexOf(f);
  if (i < 0) return null;
  const out = [];
  for (let j = i + 1; j < argv.length && !argv[j].startsWith("--"); j++) out.push(argv[j]);
  return out;
};
const limit = Number((listAfter("--limit") || [])[0] || Infinity);

// ---- chọn unit
let units = JSON.parse(readFileSync(join(REPO, "data", "units.json"), "utf8"));
units.sort((a, b) => a.topo_level - b.topo_level || a.order - b.order);
if (flag("--smoke")) {
  const ids = new Set(readFileSync(join(REPO, "data", "smoke_test_units.txt"), "utf8")
    .split(/\r?\n/).filter(Boolean).map((l) => l.split(/\s+/)[0]));
  units = units.filter((u) => ids.has(u.id));
}
const ids = listAfter("--ids");
if (ids) units = units.filter((u) => ids.includes(u.id));

const todo = units.filter((u) => {
  const d = join(REPO, "units", u.id);
  if (!existsSync(join(d, "prompt.md"))) return false;
  return flag("--force") || !existsSync(join(d, "response.md"));
}).slice(0, limit);

const missingPrompt = units.filter((u) => !existsSync(join(REPO, "units", u.id, "prompt.md"))).length;
console.log(`Cần gọi: ${todo.length} unit` + (missingPrompt ? ` (bỏ qua ${missingPrompt} unit chưa có prompt.md – chạy render_prompt.py)` : ""));
if (flag("--dry-run")) {
  todo.forEach((u) => console.log(`  ${u.id}  ${u.name}`));
  process.exit(0);
}

// ---- gọi Claude Code CLI: 1 lần gọi = 1 prompt, không tool, không lưu phiên
function callClaude(prompt) {
  return new Promise((resolve) => {
    // --system-prompt + --setting-sources "" + --strict-mcp-config: KHÔNG gửi kèm system prompt mặc định của Claude Code,
    // CLAUDE.md, memory, MCP của máy -> model chỉ nhận đúng prompt.md (~65k -> ~1k token phụ mỗi lần gọi)
    const cmd = `claude -p --model ${MODEL} --effort ${EFFORT} --tools "" --output-format json --no-session-persistence ` +
      `--system-prompt "${SYSTEM}" --setting-sources "" --strict-mcp-config`;
    const child = spawn(cmd, { shell: true, cwd: REPO });
    let out = "", err = "";
    const timer = setTimeout(() => { child.kill(); err += "\n[timeout]"; }, TIMEOUT_MS);
    child.stdout.on("data", (b) => (out += b));
    child.stderr.on("data", (b) => (err += b));
    child.on("close", (code) => {
      clearTimeout(timer);
      const line = out.trim().split(/\r?\n/).reverse().find((l) => l.startsWith("{"));
      let json = null;
      try { json = JSON.parse(line); } catch { /* xử lý bên dưới */ }
      resolve({ code, json, out, err });
    });
    child.stdin.end(prompt);
  });
}

function extractTest(text, uid) {
  const blocks = [...text.matchAll(/```(?:cpp|c\+\+)?\s*\n([\s\S]*?)```/g)].map((m) => m[1]);
  const block = blocks.find((b) => /^\s*\/\/\s*FILE:/m.test(b)) || blocks.at(-1);
  if (!block) return null;
  // luôn lưu tên <id>_test.cc (không theo tên LLM ghi, tránh ghi đè source.cc / file khác trong thư mục unit)
  return { name: `${uid}_test.cc`, code: block };
}

// ---- chạy
const logFile = join(REPO, "logs", "raw", "generate.log");
mkdirSync(dirname(logFile), { recursive: true });
const log = (s) => { console.log(s); appendFileSync(logFile, `${new Date().toISOString()} ${s}\n`); };

let ok = 0, fail = 0;
for (const [i, u] of todo.entries()) {
  const d = join(REPO, "units", u.id);
  const prompt = readFileSync(join(d, "prompt.md"), "utf8");
  const t0 = Date.now();
  const r = await callClaude(prompt);
  const secs = ((Date.now() - t0) / 1000).toFixed(0);
  const msg = r.json?.result ?? (r.out || r.err).slice(0, 300);
  if (!r.json || r.json.is_error || r.json.type !== "result") {
    fail++;
    log(`[${i + 1}/${todo.length}] ${u.id} LỖI (${secs}s): ${String(msg).slice(0, 200)}`);
    if (STOP_PATTERNS.test(String(msg)) || STOP_PATTERNS.test(r.err)) {
      log("Dừng: lỗi đăng nhập hoặc hết lượt dùng. Chạy lại lệnh này sau để tiếp tục.");
      break;
    }
    continue;
  }
  writeFileSync(join(d, "response.md"), r.json.result, "utf8");
  const test = extractTest(r.json.result, u.id);
  if (test) writeFileSync(join(d, test.name), test.code, "utf8");
  ok++;
  const tok = r.json.usage ? ` ${r.json.usage.input_tokens + (r.json.usage.cache_read_input_tokens || 0) + (r.json.usage.cache_creation_input_tokens || 0)}→${r.json.usage.output_tokens} tok` : "";
  log(`[${i + 1}/${todo.length}] ${u.id} OK (${secs}s${tok})${test ? "" : " – KHÔNG tìm thấy khối code"}`);
}
console.log(`Xong: ${ok} thành công, ${fail} lỗi. Log: logs/raw/generate.log`);
