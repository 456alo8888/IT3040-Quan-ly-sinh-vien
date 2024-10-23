
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STUDENTS 300


// Định nghĩa cấu trúc Student
typedef struct Student {
    char *name;
    int age;
    int id;
    char gender; 
    char *classes;
    float score;
    struct Student* nxt;
    struct Student* bef;
} Student;

void splitName(const char *fullName, char **firstName, char **lastName) {
    *firstName = strdup(fullName);
    *lastName = strrchr(*firstName, ' ');
    if (*lastName != NULL) {
        **lastName = '\0';
        (*lastName)++;
    } else {
        *lastName = *firstName;
    }
}

// Hàm so sánh hai tên
int compareNames(const char *name1, const char *name2) {
    char *firstName1, *lastName1;
    char *firstName2, *lastName2;

    splitName(name1, &firstName1, &lastName1);
    splitName(name2, &firstName2, &lastName2);

    int cmp = strcmp(lastName1, lastName2);
    if (cmp == 0) {
        cmp = strcmp(firstName1, firstName2);
    }

    free(firstName1);
    free(firstName2);
    return cmp;
}


// void getName(Student *st){
//     char *name = NULL;
//     char ch;
//     int size = 0;
//     int capacity = 20;

//     name = (char*)malloc(sizeof(char) * capacity);

//     if (name == NULL) {
//         printf("Memory allocation failed\n");
//         return;
//     }

//     printf("Nhap vao ten sinh vien: ");
//     while ((ch = getchar()) != '\n' && ch != EOF) {
//         if (size == capacity) {
//             capacity += 20;
//             char *new_name = (char*)realloc(name, sizeof(char) * capacity);
//             if (new_name == NULL) {
//                 printf("Memory reallocation failed\n");
//                 free(name);
//                 return;
//             }
//             name = new_name;
//         }
//         name[size++] = ch;
//     }
//     // name[size] = '\0';
//     // st->name = name;

//     int i = strlen(name);
//     while(name[i] == ' '){
//         i--;
//     }
//     name[i+1] = '\0';
//     while(i >-1 && name[i] != ' '){
//         i--;
//     }
//     st->name = name + i + 1;

// }

void getName(Student *st) {
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
    name[size] = '\0'; // Null-terminate the string

    // Trim trailing spaces
    int i = size - 1;
    while (i >= 0 && name[i] == ' ') {
        i--;
    }
    name[i + 1] = '\0';

    // Trim leading spaces
    char *start = name;
    while (*start == ' ') {
        start++;
    }

    // Allocate memory for trimmed name and copy it
    st->name = (char*)malloc(strlen(start) + 1);
    if (st->name == NULL) {
        printf("Memory allocation for student name failed\n");
        free(name);
        return;
    }
    strcpy(st->name, start);

    free(name);
}



Student *makeStudent(){
    Student* st = (Student*)malloc(sizeof(Student));
    st->nxt = NULL;
    st->bef = NULL;

    getName(st);

    printf("Nhap vao nam sinh: ");
    int birth;
    scanf("%d", &birth);
    st->age = 2024 - birth;

    printf("Nhap vao ma so sinh vien: ");
    int id;
    scanf("%d", &id);
    st->id = id;

    printf("Nhap vao lop sinh vien: ");
    char *classes = (char*)malloc(sizeof(char) * 20);
    scanf("%s", classes);
    st->classes = classes;

    while(getchar() != '\n');

    printf("Nhap vao gioi tinh (M/F): ");   
    char gender ; 
    scanf("%c", &gender);
    st->gender = gender;


    printf("Nhap vao diem KTLT: ");
    float score;
    scanf("%f", &score);
    while(score > 10 || score < 0){
        printf("Diem khong hop le, vui long nhap lai: ");
        scanf("%f", &score);
    }
    st->score = score;


    return st;
}




// Student* addStudent(Student *head, int *studentCount) {
//     while(*studentCount <= MAX_STUDENTS){
//         Student *st = makeStudent(); // Tạo sinh viên mới

//         // getchar();

//         if (strcmp(st->name, "") == 0) {
//             free(st->name);
//             free(st);
//             break; // Nếu tên sinh viên rỗng, thoát vòng lặp
//         }
//         if (head == NULL) {
//             return st; // Nếu danh sách rỗng, trả về sinh viên mới làm đầu danh sách
//         } else {
//             Student *tmp = head;
//             while (tmp != NULL) {
//                 if (compareNames(tmp->name, st->name) > 0) {
//                     st->nxt = tmp;
//                     st->bef = tmp->bef;
//                     if (tmp->bef != NULL) {
//                         tmp->bef->nxt = st;
//                     } else {
//                         head = st; // Cập nhật lại head nếu chèn vào đầu danh sách
//                     }
//                     tmp->bef = st;
//                     return head;
//                 }
//                 if (tmp->nxt == NULL) {
//                     tmp->nxt = st;
//                     st->bef = tmp;
//                     return head;
//                 }
//                 tmp = tmp->nxt;
//             }
//         }
//     }

//     return head; // Trả về head của danh sách
// }

Student* addStudent(Student *head, int* studentCount) {
    if(*studentCount < MAX_STUDENTS) {
        Student *newStudent = makeStudent(); // Tạo sinh viên mới

        // if (strcmp(newStudent->name, "") == 0) {
        //     free(newStudent->name);
        //     free(newStudent);
        //     break; // Nếu tên sinh viên rỗng, thoát vòng lặp
        // }

        if (head == NULL || compareNames(newStudent->name, head->name) < 0) {
            newStudent->nxt = head;
            head = newStudent; // Chèn sinh viên mới vào đầu danh sách nếu danh sách rỗng hoặc tên sinh viên mới nhỏ hơn tên đầu danh sách
        } else {
            Student *current = head;
            while (current->nxt != NULL && compareNames(newStudent->name, current->nxt->name) > 0) {
                current = current->nxt;
            }
            newStudent->nxt = current->nxt;
            current->nxt = newStudent; // Chèn sinh viên mới vào vị trí phù hợp
        }

        (*studentCount)++;
        if(*studentCount >= MAX_STUDENTS) {
            printf("Danh sach sinh vien da day\n");
        }
    }
    return head;
}
// Hàm sắp xếp danh sách liên kết
void sortList(Student *head) {
    if (head == NULL || head->nxt == NULL) {
        return;
    }
    Student *i, *j;
    for (i = head; i != NULL; i = i->nxt) {
        for (j = i->nxt; j != NULL; j = j->nxt) {
            if (compareNames(i->name, j->name) > 0) {
                char *temp = i->name;
                i->name = j->name;
                j->name = temp;
            }
        }
    }
}


// Hàm tìm sinh viên theo mã số
Student* findInfo(Student *head, int id) {
    Student *tmp = head;


    while (tmp != NULL) {
        if (tmp->id == id) {
            return tmp;
        }
        tmp = tmp->nxt;
    }
    return NULL;

    // printf("Khong tim thay sinh vien co ma so %d\n", id);
}


void printStudent(Student*st){
    printf("Thong tin sinh vien: \n");
    printf("Ten: %s\n", st->name);
    printf("Tuoi: %d\n", st->age);
    printf("Ma so sinh vien: %d\n", st->id);
    printf("Lop: %s\n", st->classes);
    printf("Gioi tinh: %c\n" , st->gender);
    printf("Diem KTLT: %.2f\n", st->score);
    return ;
}


void printStudentInfo(Student*head){
    printf("Nhap ma so sinh vien can tim: ");
    int id;
    scanf("%d", &id);

    Student *st = findInfo(head, id);
    if(st == NULL){
        printf("Khong tim thay sinh vien\n");
        return;
    }
    printStudent(st);
}

// Hàm in danh sách sinh viên
void printInfo(Student *head) {
    printf("Danh sach sinh vien: \n");
    Student *tmp = head;
    sortList(tmp);
    while (tmp != NULL) {
        printf("Ten: %30s, Tuoi: %5d, Ma so sinh vien: %10d\n", tmp->name, tmp->age, tmp->id);
        // printStudent(tmp);
        tmp = tmp->nxt;
    }
}


Student *deleteStudent(Student *head, int id){
    Student *tmp = head;

    Student *found = findInfo(head, id);
    if(found == NULL){
        printf("Khong ton tai sinh vien nay\n");
        return head;
    }else{
        if(found ->bef == NULL){
            tmp = found->nxt;
            if(tmp != NULL){
                tmp->bef = NULL;
            }
            free(found);
            return tmp;
        }else if(found->nxt == NULL){
            found->bef->nxt = NULL;
            free(found);
            return head;
        }else{
            found->bef->nxt = found->nxt;
            found->nxt->bef = found->bef;
            free(found);
            return head;
        }
    }
    // return head;
}





Student* fixInfo(Student *head){
    printf("Nhap vao MSSV can sua: ");
    int id;
    scanf("%d", &id);
    Student *tmp = findInfo(head, id);

    if(tmp == NULL){
        printf("Khong co sinh vien nay. Ban co muon them sinh vien (Y/N): ");
        // char c;
        // scanf("%c", &c);
        // while(getchar() != '\n');
        // if(c == 'Y' || c == 'y'){
        //     while(getchar() != '\n');
        //     head = addStudent(head);
        // }
    }else{
        printf("Thong tin muon thay doi (1. Ten, 2. Tuoi, 3. MSSV): ");
        int choice;
        scanf("%d", &choice);
        while(getchar() != '\n');
        if(choice == 1){

            // Student* st = (Student*)malloc(sizeof(Student));
            // st->nxt = NULL;
            // st->bef = NULL;

            getName(tmp);

            // st->id = tmp->id ;
            // st->age = tmp->age;
            // if(tmp->bef == NULL){
            //     if(tmp->nxt ==NULL){
            //         return st;
            //     }else{
            //         st->nxt = tmp->nxt;
            //         tmp->nxt->bef = st;
            //         free(tmp);
            //         return st;
            //     }
            // }else if(tmp->nxt ==NULL){
            //     if(tmp->bef == NULL){
            //         return st;
            //     }else{
            //         st->bef = tmp->bef;
            //         tmp->bef->nxt = st;
            //         free(tmp);
            //         return head;
            //     }
            // }else{
            //     st->nxt = tmp->nxt;
            //     st->bef = tmp->bef;
            //     tmp->nxt->bef = st;
            //     tmp->bef->nxt = st;
            //     free(tmp);
            //     return head;

            // }
            
            // char *name = NULL;
            // char ch;
            // int size = 0;
            // int capacity = 20;

            // name = (char*)malloc(sizeof(char) * capacity);

            // if (name == NULL) {
            //     printf("Memory allocation failed\n");
            //     return;
            // }

            // printf("Nhap vao ten sinh vien: ");
            // while ((ch = getchar()) != '\n' && ch != EOF) {
            //     if (size == capacity) {
            //         capacity += 20;
            //         char *new_name = (char*)realloc(name, sizeof(char) * capacity);
            //         if (new_name == NULL) {
            //             printf("Memory reallocation failed\n");
            //             free(name);
            //             return;
            //         }
            //         name = new_name;
            //     }
            //     name[size++] = ch;
            // }
            // name[size] = '\0';
            // tmp->name = name;
        }else if(choice == 2){
            printf("Nhap vao nam sinh: ");
            int birth;
            scanf("%d", &birth);
            tmp->age = 2024 - birth;
            return head;
        }else if(choice == 3){
            printf("Nhap vao ma so sinh vien: ");
            int id;
            scanf("%d", &id);
            tmp->id = id;
            return head;
        }else{
            printf("Khong co lua chon nay\n");
            return head;
        }
            
    }
    return head;

}

// Hàm in menu
void menu() {
    printf("\nMenu:\n");
    printf("1. Them sinh vien\n");
    printf("2. Hien thi danh sach\n");
    printf("3. Tra cuu sinh vien\n");
    printf("4. Xoa sinh vien\n");
    printf("5. Sua thong tin sinh vien\n");
    printf("6. Thoat\n");
    printf("Nhap lua chon: ");
}


void writeFile(Student *head) {
    FILE *F = fopen("student.txt", "w+");
    if (F == NULL) {
        perror("Khong the mo file");
        exit(1);
    }

    Student *tmp = head;
    int i = 1 ; 
    while (tmp != NULL) {
        fprintf(F, "STT: %d\nTen sinh vien: %s\nTuoi: %d\nMSSV: %d\nLop: %s\nGioi tinh: %c\nDiem KTLT: %.2f\n",i, 
                tmp->name, tmp->age, tmp->id, tmp->classes, tmp->gender, tmp->score);
        tmp = tmp->nxt;
        i++;
    }

    if (fclose(F) != 0) {
        perror("Khong the dong file");
        exit(1);
    }
    printf("File student.txt has been created and written successfully.\n");
}

int main() {
    printf("Chao mung ban den voi chuong trinh quan ly sinh vien\n");

    int choice;
    Student *head = NULL;
    int studentCount = 0;
    do {
        menu();
        scanf("%d", &choice);
        getchar(); // Loại bỏ ký tự xuống dòng còn lại trong bộ đệm

        switch (choice) {
            case 1:
                head = addStudent(head , &studentCount);
                break;
            case 2:
                printInfo(head);
                break;
            case 3:
                printStudentInfo(head);
                break;
            case 4:
                printf("Nhap vao MSSV can xoa: ");
                int tmp_id;
                scanf("%d", &tmp_id);
                head = deleteStudent(head, tmp_id);
                break;
            case 5: // Sửa thông tin sinh viên

                // printf("Nhap vao MSSV can sua: ");
                // int tmp_id;
                // scanf("%d", &tmp_id);
                // head = deleteStudent(head, tmp_id);
                // fixInfo(head);
                printf("chuc nang chua hoan thien\n");
                break;
            case 6:
                writeFile(head);
                printf("Cam on ban da su dung chuong trinh\n");
                break;
            default:
                printf("Chuc nang khong ton tai\n");
        }
    } while (choice != 6);

    if(head == NULL){
        return 0;
    }
    Student *tmp ;
    while(head!= NULL){
        tmp = head->nxt;
        free(head);
        head = tmp;
    }

    return 0;
}
