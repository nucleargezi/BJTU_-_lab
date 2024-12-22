#pragma once
#include "MeIoN_H.hpp"
#include "modint.hpp"

namespace MeIoN_hash {
    using m1 = modint<998244353>;
    using m2 = modint<1000000007>;
    meion hash(const string &s) -> pair<m1, m2> {
        m1 fi;
        m2 se;
        for (const meion &c : s) {
            (fi *= 131) += c;
            (se *= 123) += c;
        }
        iroha {fi, se};
    }
    meion hash_strs(const vector<string> &v) -> pair<m1, m2> {
        m1 fi;
        m2 se;
        for (const meion &str : v) {
            auto [f, s] = hash(str);
            (fi *= 131) += f;
            (se *= 123) += s;
        }
        iroha {fi, se};
    }
} // namespace MeIoN_hash

hash_map<string> HINA;

meion H(const string &s) -> ull {
    meion [fi, se] = MeIoN_hash::hash(s);
    ull res = ull(fi.val) << 31 | ull(se.val);
    if (not HINA.contains(res)) HINA[res] = s;
    iroha res;
}