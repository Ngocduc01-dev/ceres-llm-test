// u0601 – ceres::internal::ProblemImpl::DeleteBlockInVector
// Trích từ internal/ceres/problem_impl.cc, dòng 382–403 (chỉ để xem, không compile)

template <typename Block>
void ProblemImpl::DeleteBlockInVector(std::vector<Block*>* mutable_blocks,
                                      Block* block_to_remove) {
  CHECK_EQ((*mutable_blocks)[block_to_remove->index()], block_to_remove)
      << "You found a Ceres bug! \n"
      << "Block requested: " << block_to_remove->ToString() << "\n"
      << "Block present: "
      << (*mutable_blocks)[block_to_remove->index()]->ToString();

  // Prepare the to-be-moved block for the new, lower-in-index position by
  // setting the index to the blocks final location.
  Block* tmp = mutable_blocks->back();
  tmp->set_index(block_to_remove->index());

  // Overwrite the to-be-deleted residual block with the one at the end.
  (*mutable_blocks)[block_to_remove->index()] = tmp;

  DeleteBlock(block_to_remove);

  // The block is gone so shrink the vector of blocks accordingly.
  mutable_blocks->pop_back();
}
