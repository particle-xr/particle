namespace particle::state {

/// A retention-policy which will cause the to-be-exported state file to be
/// discarded if an existing state file is present.
class Discard;
/// A retention-policy which will cause the previously exported state file to be
/// overwritten, if it is present.
class Overwrite;
/// A retention-policy which will cause the previously exported state file to be
/// moved prior to exporting a new state file.
class Rotate;

template<class P = Rotate>
class RetentionPolicy
{
public:
  using type = RetentionPolicy;
  using policy_type = P;

  void operator()();
};

extern template class RetentionPolicy<Discard>;
extern template class RetentionPolicy<Overwrite>;
extern template class RetentionPolicy<Rotate>;

};
