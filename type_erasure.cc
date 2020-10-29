#include <iostream>
#include <utility>

// Type erasure: To access APIs of different types without knowing the types.
// Does not seem useful given the Concept in C++20.
struct Object {
  struct ObjectInterface {
    virtual void Call() = 0;
  };

  template <typename T> struct ObjectModel : public ObjectInterface {
    ObjectModel(T t) : t_(std::move(t)) {}

    void Call() {
      t_.Call();
    }

    T t_;
  };

  template <typename T>
  Object(T t) : o_(new ObjectModel<T>(t)) {}

  void Call() { o_->Call(); }

  ObjectInterface* o_ = nullptr;
};

struct CallObject {
  void Call() {
    std::cout << "call" << std::endl;
  }
};

struct CallObject2 {
  void Call() {
    std::cout << "call" << std::endl;
  }
}

int main() {
  int i = 0;
  Object object(CallObject{});
  object.Call();
}
