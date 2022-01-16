namespace mystl {
	template <typename Iter>
	void merge(Iter first, Iter mid, Iter last) {
		auto i = first, j = mid, cur = 0;
		typename Iter::value_type tmp[last-first];
		while(i != mid && j != last) {
			if((*i) < (*j)) tmp[cur++] = *i++;
			else tmp[cur++] = *j++;
		}
		while(i != mid) tmp[cur++] = *i++;
		while(j != last) tmp[cur++] = *j++;
		cur = 0;
		for(auto it = first; it != last; it++) *it = tmp[cur++];
	}
	template <typename Iter>
	void mergesort(Iter first, Iter last) {
		int n = last-first;
		if(n >= 2) {
			auto mid = first + n/2;
			mergesort(first, mid);
			mergesort(mid, last);
			merge(first, mid , last);
		}
	}
}