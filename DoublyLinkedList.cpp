#include <iostream>
#include <sstream>
#include <time.h>

//CLASS LIST BEGIN
template<typename T>
class list {
public:
	struct node {
		T data;
		node* prev;
		node* next;
		node(const T& m_data, node* m_prev, node* m_next)
			: data(m_data), prev(m_prev), next(m_next) {

		}

		node(T&& m_data, node* m_prev, node* m_next)
			: data(m_data), prev(m_prev), next(m_next) {

		}

		~node() {
			/*delete next;
			next = nullptr;*/
		}
	};

	unsigned get_length() const noexcept {
		return length;
	}

	void insert_on_begin(const T& m_data) {
		auto new_head = new node(m_data, nullptr, head);
		if (tail == nullptr) {
			tail = new_head;
		}
		else {
			head->prev = new_head;
		}
		head = new_head;
		length++;
	}

	void insert_on_end(const T& m_data) {
		auto new_tail = new node(m_data, tail, nullptr);
		if (tail != nullptr) {
			tail->next = new_tail;
		}
		else {
			head = new_tail;
		}

		tail = new_tail;
		length++;
	}

	void delete_first_element() {
		if (length > 0) {
			if (head->next != nullptr) {
				head = head->next;
				delete head->prev;
				head->prev = nullptr;
			}
			else {
				delete head;
				head = nullptr;
				tail = nullptr;
			}
			length--;
		}
	}

	void delete_last_element() {
		if (length > 0) {
			if (tail->prev != nullptr) {
				tail = tail->prev;
				delete tail->next;
				tail->next = nullptr;
			}
			else {
				delete tail;
				tail = nullptr;
				head = nullptr;
			}
			length--;
		}
	}

	std::string to_string() const {
		if (length == 0) {
			return "[]";
		}
		std::ostringstream str;
		str << "[" << head->data;
		for (auto p = head->next; p; p = p->next) {
			str << ", " << p->data;
		}
		str << "]";
		return str.str();
	}

	template<typename Comp>
	node* find_element(const T& el, Comp comp) const {
		for (auto p = head; p; p = p->next) {
			if (comp(el, p->data)) {
				return p;
			}
		}
		return nullptr;
	}

	template<typename Comp>
	bool delete_element(const T& el, Comp comp) {
		for (auto p = head; p; p = p->next) {

			if (comp(el, p->data)) {
				if (p == head && p == tail) {
					delete p;
					head = nullptr;
					tail = nullptr;
				}
				else
					if (p == head && head->next) {
						head = p->next;
						delete head->prev;
						head->prev = nullptr;
					}
					else
						if (p == tail) {
							tail = tail->prev;
							delete tail->next;
							tail->next = nullptr;
						}
						else {
							p->prev->next = p->next;
							p->next->prev = p->prev;
							delete p;
							p = nullptr;
						}
				length--;
				return true;

			}
		}
		return false;
	}

	T find_nth_element(int n) const {
		if (n < 0 || n >= length) {
			throw std::out_of_range("Index is out of range");
		}
		if (n > 0) {
			int counter = 0;
			for (auto p = head; p && counter <= n; p = p->next, counter++) {
				if (counter == n) {
					return p->data;
				}
			}
		}
		else {
			return head->data;
		}
	}

	void change_nth_element(int n, T new_data) {
		if (n < 0 || n >= length) {
			throw std::out_of_range("Index is out of range of the list");
		}
		if (n > 0) {
			int counter = 0;
			for (auto p = head; p && counter <= n; p = p->next, counter++) {
				if (counter == n) {
					p->data = new_data;
				}
			}
		}
		else {
			head->data = new_data;
		}
	}

	template <typename Comp>
	void insert_element(const T& new_data, Comp comp) {
		for (auto p = head; p; p = p->next) {
			if (comp(new_data, p->data)) {
				if (p == head) {
					insert_on_begin(new_data);
				}
				else if (p == tail) {
					auto nd = new node(new_data, tail->prev, tail);
					tail->prev->next = nd;
					tail->prev = nd;
					length++;

				}
				else {
					auto nd = new node(new_data, p->prev, p);
					p->prev->next = nd;
					p->prev = nd;
					length++;
				}
				return;
			}

		}
		insert_on_end(new_data);
	}

	void delete_all() {
		while (length > 0) {
			delete_first_element();
		}
	}

	list() noexcept : head(nullptr), tail(nullptr), length(0) {

	}

	list(list&& lst) noexcept
		: head(lst.head), tail(lst.tail), length(lst.length) {
		lst.head = nullptr;
		lst.tail = nullptr;
		lst.length = 0;
	}

	~list() {
		delete head;
		head = nullptr;
		length = 0;
	}

private:
	node* head;
	node* tail;
	unsigned length;
};
// CLASS LIST END

struct some_class {
	int some_int;
	std::string some_string;
};

bool f_komp(const some_class& a, const some_class& b) {
	return a.some_int == b.some_int;
}

std::ostream& operator<<(std::ostream& out, const some_class& obj) {
	out << obj.some_int;
	out << obj.some_string;
	return out;
}

some_class generate_data() {
	int number = rand() % 1000;
	std::string text;
	for (int i = 0; i < 10; i++) {
		char sign = rand() % 42 + 48;
		text.append(1, sign);
	}
	some_class data{ number, text };
	return data;
}

int main()
{
	auto komp = [](const some_class& a, const some_class& b) {
		return a.some_int == b.some_int;
		};

	auto new_komp = [](const some_class& a, const some_class& b) {
		return a.some_int < b.some_int;
		};

	list<some_class>* lista = new list<some_class>();
	const int MAX_ORDER = 6;
	srand(time(0));
	for (int o = 1; o <= MAX_ORDER; o++) {
		const int n = pow(10, o);

		clock_t t1 = clock();
		for (int i = o; i < n; i++) {
			lista->insert_on_begin(generate_data());
		}
		clock_t t2 = clock();
		std::cout << "Czas na wygenerowanie danych i uzupelnienie listy: " << std::endl;
		std::cout << (t2 - t1) / double(CLOCKS_PER_SEC) << std::endl;

		const int m = pow(10, 4);
		t1 = clock();
		for (int i = 0; i < m; i++) {
			some_class temp = generate_data();
			lista->delete_element(temp, komp);
		}
		t2 = clock();
		std::cout << "Czas na znalezienie i usuniecie wezla: " << std::endl;
		std::cout << (t2 - t1) / double(CLOCKS_PER_SEC) << std::endl << std::endl;

		lista->delete_all();
	}

	return 0;
}
