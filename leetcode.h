#include <algorithm>
#include <array>
#include <atomic>
#include <bit>
#include <bitset>
#include <chrono>
#include <deque>
#include <execution>
#include <format>
#include <forward_list>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numbers>
#include <numeric>
#include <queue>
#include <random>
#include <ranges>
#include <regex>
#include <set>
#include <span>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_set>
#include <utility>

#ifndef LIST_NODE
#define LIST_NODE

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

#endif

#ifndef LIST_NODE
#define LIST_NODE

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

#endif

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

#ifndef NODE_DEF_
#define NODE_DEF_

// Definition for a Node.
class Node {
public:
  int val;
  std::vector<Node *> children;

  Node() {}

  Node(int _val) { val = _val; }

  Node(int _val, std::vector<Node *> _children) {
    val = _val;
    children = _children;
  }
};

#endif

#ifndef NODE_DEF_
#define NODE_DEF_

// Definition for a Node.
class Node {
public:
  int val;
  Node *left;
  Node *right;
  Node *next;

  Node() : val(0), left(NULL), right(NULL), next(NULL) {}

  Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

  Node(int _val, Node *_left, Node *_right, Node *_next)
      : val(_val), left(_left), right(_right), next(_next) {}
};

#endif

#ifndef NODE_DEF_
#define NODE_DEF_

// Definition for a Node.
class Node {
public:
  int val;
  std::vector<Node *> neighbors;
  Node() {
    val = 0;
    neighbors = std::vector<Node *>();
  }
  Node(int _val) {
    val = _val;
    neighbors = std::vector<Node *>();
  }
  Node(int _val, std::vector<Node *> _neighbors) {
    val = _val;
    neighbors = _neighbors;
  }
};

#endif

//  Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.
class Iterator {
  struct Data;
  Data *data;

public:
  Iterator(const std::vector<int> &nums);
  Iterator(const Iterator &iter);

  // Returns the next element in the iteration.
  int next();

  // Returns true if the iteration has more elements.
  bool hasNext() const;
};

template <typename T, typename U>
std::ostream &operator<<(std::ostream &, const std::pair<T, U> &);

template <typename T>
std::ostream &operator<<(std::ostream &, const std::vector<T> &);

template <typename T, size_t N>
std::ostream &operator<<(std::ostream &os, const std::array<T, N> &a) {
  if (std::empty(a))
    return os << "[]";

  for (os << '['; const auto &x : a)
    os << x << ',';

  return os << '\b' << ']';
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
  if (std::empty(v))
    return os << "[]";

  for (os << '['; const auto &x : v)
    os << x << ',';

  return os << '\b' << ']';
}

std::ostream &operator<<(std::ostream &os_, const std::vector<bool> &v_) {
  if (std::empty(v_))
    return os_ << "[]";

  for (os_ << "[" << std::boolalpha; auto &&x : v_)
    os_ << x << ',';

  return os_ << std::noboolalpha << "\b]";
}

template <typename T, typename U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p) {
  return os << '[' << p.first << ' ' << p.second << ']';
}

std::ostream &operator<<(std::ostream &os_, const ListNode *n_) {
  if (n_ == nullptr)
    return os_ << "[]";

  os_ << '[';

  for (; n_ != nullptr; n_ = n_->next)
    os_ << n_->val << ',';

  return os_ << "\b]";
}

ListNode *make_list(std::span<int> s_ = {}) {
  if (std::empty(s_))
    return nullptr;

  auto n{new ListNode{s_.front()}};
  n->next = make_list(s_.subspan(1));

  return n;
}

ListNode *make_list(auto &&x, auto &&...y) {
  if constexpr (sizeof...(y) == 0)
    return new ListNode{x};
  else
    return new ListNode{x, make_list(std::forward<decltype(y)>(y)...)};
}

TreeNode *make_tree(std::span<std::string> s, int i = 0) {
  if (i >= std::size(s) || s[i] == "null")
    return nullptr;

  auto t{new TreeNode{std::stoi(s[i])}};
  t->left = make_tree(s, i * 2 + 1);
  t->right = make_tree(s, i * 2 + 2);

  return t;
}

TreeNode *make_tree(std::span<int> s, int i = 0) {
  if (i >= std::size(s) || s[i] == 0)
    return nullptr;

  auto t{new TreeNode{s[i]}};
  t->left = make_tree(s, i * 2 + 1);
  t->right = make_tree(s, i * 2 + 2);

  return t;
}

std::ostream &operator<<(std::ostream &os_, const TreeNode *n_) {
  for (std::deque d{n_}; !std::empty(d); os_ << '\n') {
    for (auto n{std::size(d)}; n > 0; --n) {
      os_ << (d.front() == nullptr ? "n "
                                   : std::to_string(d.front()->val) + " ");
      if (d.front() != nullptr)
        d.push_back(d.front()->left), d.push_back(d.front()->right);
      d.pop_front();
    }
  }

  return os_;
}

template <typename T> struct recursive final {
  const T F;

  constexpr recursive(T &&F) : F(std::forward<T>(F)) {}

  template <typename... Args>
  constexpr decltype(auto) operator()(Args &&...A) const noexcept {
    return F(std::cref(*this), std::forward<Args>(A)...);
  }
};

inline static constexpr struct {
  constexpr decltype(auto) operator()(auto &&fn,
                                      auto &&...args) const noexcept {
    return recursive{std::forward<decltype(fn)>(fn)}(
        std::forward<decltype(args)>(args)...);
  }
} recurse{};

std::vector<std::string> split(std::string_view S, char D = ' ') {
  std::vector<std::string> V;
  for (auto I = std::cbegin(S), E = std::cend(S); I != E;) {
    I = std::find_if(I, E, [D](char C) { return C != D; });
    if (I == E)
      break;
    auto J = std::find(I, E, D);
    V.emplace_back(I, J);
    if (J == E)
      break;
    I = J + 1;
  }
  return V;
}

inline static constexpr struct {
  using point = std::pair<int, int>;
  using vec = std::pair<int, int>;

  constexpr int operator()(point a, point b, point c) const noexcept {
    return this->operator()({b.first - a.first, b.second - a.second},
                            {c.first - b.first, c.second - b.second});
  }

  constexpr int operator()(vec a, vec b) const noexcept {
    return a.first * b.second - a.second * b.first;
  }
} cross_product{};

template <size_t N> struct union_find final {
  std::array<int, N> p{}, r{};

  constexpr union_find() { iota(begin(p), end(p), 0); }

  constexpr int find(int i) noexcept {
    return p[i] == i ? i : p[i] = find(p[i]);
  }

  constexpr void unite(int i, int j) noexcept {
    auto x{find(i)}, y{find(j)};

    if (r[x] < r[y])
      swap(x, y);

    r[x] += static_cast<int>(r[x] == r[y]);

    p[y] = x;
  }
};

template <size_t N> struct fenwick final {
  std::array<int, N> a = {};

  constexpr void add(int i, int x) noexcept {
    for (; i < N; i += i & -i)
      a[i] += x;
  }

  constexpr int find(int i) noexcept {
    int x = 0;
    for (; i != 0; i -= i & -i)
      x += a[i];
    return x;
  }
};

template <std::size_t N> struct dijkstra final {
  using graph_t =
      std::array<std::vector<std::pair<std::size_t, std::size_t>>, N>;
  std::array<std::size_t, N> operator()(graph_t a, std::size_t src) {
    std::priority_queue<std::pair<int, int>> q;
    std::array<std::size_t, N> d;

    std::ranges::fill(d, std::numeric_limits<std::size_t>::max());

    q.emplace(0, src);

    for (; !std::empty(q);) {
      auto [x, y] = q.top();
      q.pop();

      if (x > d[y])
        continue;

      d[y] = x;

      for (auto &&[v, e] : a[y]) {
        if (d[v] > x + e) {
          d[v] = x + e;
          q.emplace(x + e, v);
        }
      }
    }

    return d;
  }
};

template <std::size_t N> struct dijkstra_path final {
  using graph_t =
      std::array<std::vector<std::pair<std::size_t, std::size_t>>, N>;
  std::array<std::size_t, N> operator()(graph_t a, std::size_t src) {
    std::priority_queue<std::pair<int, int>> q;
    std::array<std::size_t, N> d;
    std::array<std::size_t, N> p;

    std::ranges::fill(d, std::numeric_limits<std::size_t>::max());
    std::iota(std::begin(p), std::end(p), 0);

    q.emplace(0, src);

    for (; !std::empty(q);) {
      auto [x, y] = q.top();
      q.pop();

      if (x > d[y])
        continue;

      d[y] = x;

      for (auto &&[v, e] : a[y]) {
        if (d[v] > x + e) {
          d[v] = x + e;
          p[v] = y;
          q.emplace(x + e, v);
        }
      }
    }

    return p;
  }
};

template <std::size_t N> struct dijkstra_path_dist final {
  using graph_t =
      std::array<std::vector<std::pair<std::size_t, std::size_t>>, N>;
  std::pair<std::array<std::size_t, N>, std::array<std::size_t, N>>
  operator()(graph_t a, std::size_t src) {
    std::priority_queue<std::pair<int, int>> q;
    std::array<std::size_t, N> d;
    std::array<std::size_t, N> p;

    std::ranges::fill(d, std::numeric_limits<std::size_t>::max());
    std::iota(std::begin(p), std::end(p), 0);

    q.emplace(0, src);

    for (; !std::empty(q);) {
      auto [x, y] = q.top();
      q.pop();

      if (x > d[y])
        continue;

      d[y] = x;

      for (auto &&[v, e] : a[y]) {
        if (d[v] > x + e) {
          d[v] = x + e;
          p[v] = y;
          q.emplace(x + e, v);
        }
      }
    }

    return {d, p};
  }
};

struct trie final {
  struct node final {
    std::array<node *, 27> a = {};
    int n = 0;
  };

  node *t = new node;

  void insert(std::string s) {
    s.push_back('z' + 1);
    for (node *n = t; auto &&x : s) {
      if (n->a[x - 'a'] == nullptr)
        n->a[x - 'a'] = new node;
      n->n++;
      n = n->a[x - 'a'];
    }
  }

  int search(std::string_view s) {
    int y = 0;
    for (node *n = t; auto &&x : s) {
      y += n->n;
      n = n->a[x - 'a'];
    }
    return y;
  }
};