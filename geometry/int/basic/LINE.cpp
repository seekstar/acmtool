struct LINE {
    VEC s, v;

	//-1: left
    //0: on it
    //1: right
    int relation(const VEC& p) const {
        return sgn((p - s) ^ v);
    }
};
