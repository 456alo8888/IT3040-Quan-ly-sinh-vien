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

typedef struct Classes{
    char *class_name;
    int numStudents;
    struct Classes *next;
    Student *firstStudent;
} Classes;


char class_name[30];
Classes *class_list = NULL;
int numClasses = 0;





Classes* make_Class(char *class_name){
    Classes* newClass = (Classes*)malloc(sizeof(Classes));
    int tmp = strlen(class_name);
    newClass->class_name = (char*)malloc(sizeof(char) * (tmp+1));
    strcpy(newClass->class_name,class_name);
    newClass->numStudents = 0;
    newClass->firstStudent = NULL;
    newClass->next = NULL;
    return newClass;
}

void print_class_list_info(){
    printf("\nDanh sach hien tai co %d lop nhu sau: \n", numClasses);
    Classes* tmp = class_list;
    int stt = 1;
    while(tmp!=NULL){
        printf("%d. %s\n", stt++, tmp->class_name);
        tmp=tmp->next;
    }
    printf("\n ---- Hoan thanh viec in danh sach lop ----\n");
    // printf("\nNhap 0 de quay lai menu: ");
}

void addClass(Classes *newClass){
    if(class_list==NULL){
        class_list = newClass;
        return;
    }
    if(strcmp(class_list->class_name,newClass->class_name)>=0){
        newClass->next = class_list;
        class_list = newClass;
        return;
    }
    Classes* tmp = class_list;
    while(tmp->next!=NULL && strcmp(tmp->next->class_name,newClass->class_name)<=0) tmp = tmp->next;
    if(tmp->next==NULL) tmp->next = newClass;
    else{
        Classes* tam = tmp->next;
        tmp->next = newClass;
        newClass->next = tam;
    }
}

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

// Student* makeStudent(){
//     Student* st = (Student*)malloc(sizeof(Student));
//     st->nxt = NULL;
//     getName(st);
//     return st;
// }

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



Student* addStudent(Classes *tmp) {
    if(tmp== NULL){
        printf("Lop khong ton tai, hay tao lop\n");
        addClass(make_Class(class_name));
        return NULL;
    }

    Student*head = tmp->firstStudent;
    
    while(tmp->numStudents < MAX_STUDENTS) {
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

        tmp->numStudents++;
        if(tmp->numStudents >= MAX_STUDENTS) {
            printf("Danh sach sinh vien da day\n");
        }
    }
    return head;
}


void fill_info_Class(){
    printf("\nTen cua lop moi ban muon them la: ");
    gets(class_name);
    Classes* u = make_Class(class_name);
    Classes* tmp = class_list;
    while(tmp!=NULL){
        if(strcmp(tmp->class_name,u->class_name)==0){
            printf("\nLop muon them da ton tai trong danh sach.\n");
            printf("\n ---- Nhap lop khong thanh cong ----\n");
            printf("\nNhap 0 de quay lai menu: ");
            return;
        }
        tmp = tmp->next;
    }
    addClass(u);
    numClasses++;
    printf("\n ---- Hoan thanh viec nhap lop ----\n");
    // printf("\nNhap 0 de quay lai menu: ");
}



void writeFile(Classes *tmp_class) {
    Student *head = tmp_class->firstStudent;
    FILE *F = fopen("student.txt", "w+");
    if (F == NULL) {
        perror("Khong the mo file");
        exit(1);
    }

    Student *tmp = head;
    int i = 1 ; 

    fprintf(F, "\nDanh sach sinh vien lop %s\n", tmp_class->class_name);
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

void freeMemory(){
    Classes *u = class_list;
    while(u!=NULL){
        Classes *un = u->next;
        Student* v = u->firstStudent;
        while(v!=NULL){
            Student *vn = v->nxt;
            free(v);
            v = vn;
        }
        free(u);
        u = un;
    }
}

// void printInfo(Student *head) {
//     printf("Danh sach sinh vien: \n");
//     Student *tmp = head;
//     while (tmp != NULL) {
//         printf("Ten: %s\n", tmp->name);
//         tmp = tmp->nxt;
//     }
// }

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

// Hàm in menu
void menu() {
    printf("\nMenu:\n");
    printf("1. Them sinh vien\n");
    printf("2. Hien thi danh sach sinh vien cua lop\n");
    printf("3. Them lop sinh vien\n");
    printf("4. Hien thi danh sach cac lop hien co\n");
    printf("5. Thoat\n");
    printf("Nhap lua chon: ");
}

Classes *found_class(char *class_name){
    Classes *tmp = class_list;
    while(tmp!=NULL){
        if(strcmp(tmp->class_name,class_name)==0){
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

int main() {
    printf("Chao mung ban den voi chuong trinh quan ly sinh vien\n");

    int choice;
    char *name_of_class;
    Classes*tmp;

    do {
        menu();
        scanf("%d", &choice);
        getchar(); // Loại bỏ ký tự xuống dòng còn lại trong bộ đệm

        switch (choice) {
            case 1:
                printf("Nhap ten lop sinh vien: ");
                //find class
                name_of_class = (char*)malloc(sizeof(char) * 30);
                gets(name_of_class);
                tmp = found_class(name_of_class);

                if(tmp== NULL){
                    printf("Lop khong ton tai, hay tao lop\n");
                    fill_info_Class();
                }
                tmp= found_class(name_of_class);
                tmp->firstStudent = makeStudent();
                break;
            case 2:
                printf("Nhap ten lop sinh vien: ");
                //find class
                name_of_class = (char*)malloc(sizeof(char) * 30);
                gets(name_of_class);
                tmp = found_class(name_of_class);

                if(tmp == NULL){
                    printf("Lop khong ton tai, hay tao lop\n");
                    fill_info_Class();
                }
                tmp = found_class(name_of_class);
                printInfo(tmp->firstStudent);
                break;
            case 3:
                fill_info_Class();
                // printf("Chuc nang chua hoan thien\n");
                break;
            case 4:
                print_class_list_info();
                // printf("Chuc nang chua hoan thien\n");
                break;

            case 5:
                tmp = class_list;
                while(tmp!=NULL){
                    writeFile(tmp);
                    tmp = tmp->next;
                }
                printf("Cam on ban da su dung chuong trinh\n");
                break;
            default:
                printf("Chuc nang khong ton tai\n");
        }
    } while (choice != 5);

    // Giải phóng bộ nhớ
    freeMemory();
    // Student *tmp;
    // while (head != NULL) {
    //     tmp = head->nxt;
    //     free(head->name);
    //     free(head);
    //     head = tmp;
    // }

    return 0;
}
