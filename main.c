#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Định nghĩa cấu trúc Student
typedef struct Student {
    char *name;
    struct Student* nxt;
} Student;

// Hàm tách lấy tên (từ cuối cùng sau khoảng trắng)
const char* getFirstName(const char *fullName) {
    const char *firstName = strrchr(fullName, ' ');
    return (firstName == NULL) ? fullName : firstName + 1;
}

// Hàm so sánh theo tên rồi đến họ
int compareStudents(const char *name1, const char *name2) {
    const char *firstName1 = getFirstName(name1);
    const char *firstName2 = getFirstName(name2);

    int cmp = strcmp(firstName1, firstName2);
    if (cmp == 0) {
        // Nếu tên giống nhau thì so sánh toàn bộ họ và tên
        return strcmp(name1, name2);
    }
    return cmp;
}

void getName(Student *st){
    char *name = NULL;
    char ch;
    int size = 0;
    int capacity = 20;

    name = (char*)malloc(sizeof(char) * capacity);

    if (name == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    printf("Nhap vao ten sinh vien: ");
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (size == capacity) {
            capacity += 20;
            char *new_name = (char*)realloc(name, sizeof(char) * capacity);
            if (new_name == NULL) {
                printf("Memory reallocation failed\n");
                free(name);
                return;
            }
            name = new_name;
        }
        name[size++] = ch;
    }
    name[size] = '\0';
    st->name = name;
}

Student* makeStudent(){
    Student* st = (Student*)malloc(sizeof(Student));
    st->nxt = NULL;

    getName(st);

    return st;
}

Student* addStudent(Student *head) {
    while (1) {
        Student *newStudent = makeStudent(); // Tạo sinh viên mới

        if (strcmp(newStudent->name, "") == 0) {
            free(newStudent->name);
            free(newStudent);
            break; // Nếu tên sinh viên rỗng, thoát vòng lặp
        }

        if (head == NULL || compareStudents(newStudent->name, head->name) < 0) {
            newStudent->nxt = head;
            head = newStudent; // Chèn sinh viên mới vào đầu danh sách nếu danh sách rỗng hoặc tên sinh viên mới nhỏ hơn tên đầu danh sách
        } else {
            Student *current = head;
            while (current->nxt != NULL && compareStudents(newStudent->name, current->nxt->name) > 0) {
                current = current->nxt;
            }
            newStudent->nxt = current->nxt;
            current->nxt = newStudent; // Chèn sinh viên mới vào vị trí phù hợp
        }
    }
    return head;
}

void printInfo(Student *head) {
    printf("Danh sach sinh vien: \n");
    Student *tmp = head;
    while (tmp != NULL) {
        printf("Ten: %s\n", tmp->name);
        tmp = tmp->nxt;
    }
}

// Hàm in menu
void menu() {
    printf("\nMenu:\n");
    printf("1. Them sinh vien\n");
    printf("2. Hien thi danh sach\n");
    printf("3. Thoat\n");
    printf("Nhap lua chon: ");
}

int main() {
    printf("Chao mung ban den voi chuong trinh quan ly sinh vien\n");

    int choice;
    Student *head = NULL;

    do {
        menu();
        scanf("%d", &choice);
        getchar(); // Loại bỏ ký tự xuống dòng còn lại trong bộ đệm

        switch (choice) {
            case 1:
                head = addStudent(head);
                break;
            case 2:
                printInfo(head);
                break;
            case 3:
                printf("Cam on ban da su dung chuong trinh\n");
                break;
            default:
                printf("Chuc nang khong ton tai\n");
        }
    } while (choice != 3);

    // Giải phóng bộ nhớ
    Student *tmp;
    while (head != NULL) {
        tmp = head->nxt;
        free(head->name);
        free(head);
        head = tmp;
    }

    return 0;
}
