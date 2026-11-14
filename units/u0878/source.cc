// u0878 – ceres::internal::Preconditioner::Options::Options
// Trích từ internal/ceres/preconditioner.h, dòng 55–66 (chỉ để xem, không compile)

    Options(const LinearSolver::Options& linear_solver_options)
        : type(linear_solver_options.preconditioner_type),
          visibility_clustering_type(
              linear_solver_options.visibility_clustering_type),
          sparse_linear_algebra_library_type(
              linear_solver_options.sparse_linear_algebra_library_type),
          num_threads(linear_solver_options.num_threads),
          row_block_size(linear_solver_options.row_block_size),
          e_block_size(linear_solver_options.e_block_size),
          f_block_size(linear_solver_options.f_block_size),
          elimination_groups(linear_solver_options.elimination_groups),
          context(linear_solver_options.context) {}
