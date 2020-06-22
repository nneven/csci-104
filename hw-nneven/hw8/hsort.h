template <typename T, typename Comparator >
void heapify(std::vector<T>& data, int loc, int effsize, Comparator& comp)
{
	int left = loc * 2 + 1;
	int right = loc * 2 + 2;
	int largest = loc;

	if (left < effsize && comp(data[left], data[largest])) largest = left;
	if (right < effsize && comp(data[right], data[largest])) largest = right;
	if (largest	!= loc)
	{
		std::swap(data[loc], data[largest]);
		heapify(data, largest, effsize, comp);
	}
}

template<typename T, typename Comparator >
void hsort(std::vector<T>& data, Comparator comp = Comparator())
{
	for (int i = data.size() / 2; i >= 0; i--)
	{
		heapify(data, i, data.size(), comp);
	}

	for (int i = data.size() - 1; i >= 0; i--)
	{
		std::swap(data[0], data[i]);
		heapify(data, 0, i, comp);
	}

}