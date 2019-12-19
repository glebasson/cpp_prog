#include <iostream>
#include <vector>
#include <complex>

template<typename T>
class Rect {
  public:
  T getw();
  T geth();

  private:
  T w, h;
};

template<typename T>
class Circle {
  public:
  T getr();

  private:
  T r;
};

template<typename T>
class Trait {
  public:
  static int size(T &obj);
};

template<typename T>
class Trait<Circle<T>> {
  public:
  static int size(const Circle<T> &obj) {
    return sizeof(T);
  }
};

template<typename T>
class Trait<Rect<T>> {
  public:
  static int size(const Rect<T> &obj) {
    return sizeof(T) * 2;
  }
};

template<typename T> struct is_complex : std::false_type {};
template<typename T> struct is_complex<std::complex<T>> : std::true_type {};

template<typename T>
class Polynomial {
  public:
  Polynomial(std::vector<T> v) : coeff(v) {}
  std::vector<T> coeff;

  Polynomial<T> operator*(T k) {
    std::vector<T> temp(coeff.size());
    for(int i = 0; i < coeff.size(); ++i) {
      temp[i] = coeff[i] * k;
    }
    return Polynomial(temp);
  }

  Polynomial<T> operator-(Polynomial<T> k) {
    std::vector<T> temp(coeff.size());
    for(int i = 0; i < coeff.size(); ++i) {
      temp[i] = coeff[i] - k.coeff[i];
    }
    return Polynomial(temp);
  }

  typename std::enable_if<is_complex<T>::value, Polynomial<T>>::type Reciprocal() {
    std::vector<T> temp(coeff.size());
    for(int i = 0; i < coeff.size(); ++i) {
      temp[i] = std::conj(coeff[i]);
    }
    return Polynomial(temp);
  }

};

// complex
template<typename T>
typename std::enable_if<is_complex<T>::value, Polynomial<T>>::type SchurTransform(Polynomial<T> p) {
  return  p * std::conj(p.coeff[0]) - p.Reciprocal() * p.coeff[p.coeff.size() - 1];
}

// real
template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, Polynomial<T>>::type SchurTransform(Polynomial<T> p) {
  return  p * p.coeff[0] - p * p.coeff[p.coeff.size() - 1];
}



int main() {
  // Circle<double> c;
  // std::cout << Trait<Circle<double>>::size(c) << "\n";

  // std::vector<int> a({1,2,3});
  // Polynomial<int> p(a);
  Polynomial<std::complex<float>> z({(1,2), (3,4)});
  std::complex<float> q(1,2);
  z * q;
  SchurTransform(z);
  return(0);
}