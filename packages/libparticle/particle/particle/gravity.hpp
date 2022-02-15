namespace particle {

static constexpr float G = 6.67e-11;

constexpr float
GravitationalForce(double m1, double m2, double r)
{
  return G * (m1 * m2) / (r * r);
}

}
