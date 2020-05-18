//Push a value v whose index is i into a incresing queue, whose length of corresponding interval is no more than n
template<typename T, typename Compare>
void PushIncQ(deque<pair<T, int> >& q, int n, T v, int i, Compare less) {
	while (!q.empty() && less(v, q.back().first))
		q.pop_back();
	q.push_back(make_pair(v, i));
	if (i - q.front().second >= n)
		q.pop_front();
}

