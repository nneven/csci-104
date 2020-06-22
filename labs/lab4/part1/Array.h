class Array {
public:
	Array();
	// ~Array();
	// Array(const Array& other);
	// Array& operator=(const Array& other);
	Array operator+(const Array& other) const;
	int getValAt(int index) const;
	int getSize() const;
	void push(int _val);

private:
	int* data;
	int size;
};