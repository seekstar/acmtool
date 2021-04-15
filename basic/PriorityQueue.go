type PriorityQueue []int

func NewPriorityQueue() PriorityQueue {
	return make([]int, 1)
}

func (s PriorityQueue) top() int {
	return s[1]
}

func (pq *PriorityQueue) pop() {
	s := *pq
	cur := 1
	last := len(s) - 1
	for {
		left := cur << 1
		if left > last {
			break
		}
		right := cur << 1 | 1
		if right <= last && s[right] < s[left] {
			left = right
		}
		if s[last] < s[left] {
			break
		}
		s[cur] = s[left]
		cur = left
	}
	s[cur] = s[last]
	*pq = s[:last]
}

func (pq *PriorityQueue) push(x int) {
	cur := len(*pq)
	*pq = append(*pq, 0)
	s := *pq
	for cur >> 1 != 0 && (x < s[cur >> 1]) {
		s[cur] = s[cur >> 1]
		cur >>= 1
	}
	s[cur] = x
}