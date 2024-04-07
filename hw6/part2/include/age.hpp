#ifndef AGE_HPP
#define AGE_HPP

class Age {
  private:
	int time = 0;

  public:
	int get_time() { return time; }
	Age& operator++() {
		time++;
		return *this;
	}
};
#endif	// AGE_HPP
