# Unit u0418: `ceres::internal::SubsetPreconditioner::num_rows`

The test builds a three-column block-sparse matrix, constructs a real
`SubsetPreconditioner`, calls `num_rows()`, and verifies the reported row
dimension.
