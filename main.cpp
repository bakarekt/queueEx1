#include <iostream>
#include <string>
using namespace std;

// Cấu trúc sản phẩm
struct Product {
    string name;
    int quantity;
    double price;
    Product* next;
};

// Cấu trúc node của hàng đợi
struct Node {
    Product* cart; // Danh sách sản phẩm trong giỏ hàng
    Node* next;    // Con trỏ đến node tiếp theo
};

// Cấu trúc hàng đợi
struct Queue {
    Node* front; // Con trỏ đầu hàng đợi
    Node* rear;  // Con trỏ cuối hàng đợi

    Queue() : front(nullptr), rear(nullptr) {}

    // Thêm giỏ hàng vào hàng đợi
    void enqueue(Product* cart) {
        Node* newNode = new Node{cart, nullptr};
        if (rear) {
            rear->next = newNode;
        } else {
            front = newNode;
        }
        rear = newNode;
    }

    // Xóa giỏ hàng khỏi hàng đợi
    Product* dequeue() {
        if (!front) return nullptr;
        Node* temp = front;
        Product* cart = front->cart;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
        return cart;
    }

    // Kiểm tra hàng đợi rỗng
    bool isEmpty() {
        return front == nullptr;
    }
};

// Tính tổng tiền giỏ hàng
double cartTotal(Product* cart) {
    double total = 0;
    while (cart) {
        total += cart->quantity * cart->price;
        cart = cart->next;
    }
    return total;
}

// Đếm số lượng sản phẩm A trong giỏ hàng
int countProductA(Product* cart, const string& productName) {
    int count = 0;
    while (cart) {
        if (cart->name == productName) {
            count += cart->quantity;
        }
        cart = cart->next;
    }
    return count;
}

int main() {
    Queue checkoutQueue;
    double totalRevenue = 0; // Tổng số tiền thu được
    int productACount = 0;   // Số lượng sản phẩm A đã bán
    string productA = "A";   // Tên sản phẩm A

    // Thêm dữ liệu vào hàng đợi
    for (int i = 1; i <= 3; i++) {
        Product* cart = nullptr;
        Product* last = nullptr;

        for (int j = 1; j <= 2; j++) {
            Product* product = new Product{"A", j, 10.0 * j, nullptr};
            if (!cart) {
                cart = product;
            } else {
                last->next = product;
            }
            last = product;
        }
        checkoutQueue.enqueue(cart);
    }

    // Xử lý từng khách hàng trong hàng đợi
    while (!checkoutQueue.isEmpty()) {
        Product* cart = checkoutQueue.dequeue();
        totalRevenue += cartTotal(cart);
        productACount += countProductA(cart, productA);

        // Giải phóng bộ nhớ
        while (cart) {
            Product* temp = cart;
            cart = cart->next;
            delete temp;
        }
    }

    cout << "Tong so tien thu duoc: " << totalRevenue << endl;
    cout << "So luong san pham " << productA << " : " << productACount << endl;

    return 0;
}