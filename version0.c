#include<stdio.h>
const int MAXSV = 300;
const int MAXLEN = 30;

char ds[MAXSV][MAXLEN];

// Hàm in menu
void menu() {
    printf("\nMenu:\n");
    printf("1. Them sinh vien\n");
    printf("2. Sap xep danh sach\n");
    printf("3. Hien thi danh sach\n");
    printf("4. Thoat\n");
    printf("Nhap lua chon: ");
}



int main() {
    printf("Chao mung ban den voi chuong trinh quan ly sinh vien\n");

    int choice;
    // Student *head = NULL;
    // int studentCount = 0;
    // do {
    //     menu();
    //     scanf("%d", &choice);
    //     getchar(); // Loại bỏ ký tự xuống dòng còn lại trong bộ đệm

    //     switch (choice) {
    //         case 1:
    //             head = addStudent(head , &studentCount);
    //             break;
    //         case 2:
    //             printInfo(head);
    //             break;
    //         case 3:
    //             printf("Cam on ban da su dung chuong trinh\n");
    //             break;
    //         default:
    //             printf("Chuc nang khong ton tai\n");
    //     }
    // } while (choice != 3);

    // // Giải phóng bộ nhớ
    // Student *tmp;
    // while (head != NULL) {
    //     tmp = head->nxt;
    //     free(head->name);
    //     free(head);
    //     head = tmp;
    // }



    return 0;
}
