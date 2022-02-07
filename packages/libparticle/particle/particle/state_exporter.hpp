namespace particle {

/// A retention-policy which will cause the to-be-exported state file to be
/// discarded if an existing state file is present.
class RetentionPolicy_Discard;
/// A retention-policy which will cause the previously exported state file to be
/// overwritten, if it is present.
class RetentionPolicy_Overwrite;
/// A retention-policy which will cause the previously exported state file to be
/// moved prior to exporting a new state file.
class RetentionPolicy_Rotate;

template<class P = RetentionPolicy_Rotate>
class RetentionPolicy
{
public:
  using type = RetentionPolicy;
  using policy_type = P;

  void operator()();
};

extern template class RetentionPolicy<RetentionPolicy_Discard>;
extern template class RetentionPolicy<RetentionPolicy_Overwrite>;
extern template class RetentionPolicy<RetentionPolicy_Rotate>;

};
