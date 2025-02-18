#include <stdio.h>

#define N 10

typedef struct
{
    int data[N][N];
    int rows;
    int cols;
} Matrix;

int ask(char question[]);
Matrix read_matrix(void);
Matrix multiply(const Matrix a, const Matrix b);
void display_matrix(const Matrix m);

Matrix read_matrix(void)
{
    int rows = ask("How many rows:");
    int cols = ask("How many cols:");
    if(rows > N || cols > N) {
        puts("trop grand");
        Matrix m;
        return m;
    } else {
        Matrix m;
        m.rows = rows;
        m.cols = cols;
    
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                m.data[i][j] = ask("Enter a number:");
            }
        }
    
        return m;
    }
}

void display_matrix(const Matrix m)
{
    for(int i = 0; i < m.rows; i++) {
        for(int j = 0; j < m.cols; j++) {
            printf("%d ", m.data[i][j]);
        }
        puts("");
    }
}

Matrix multiply(const Matrix a, const Matrix b)
{
    Matrix m;
    m.rows = a.rows;
    m.cols = b.cols;
    for(int i = 0; i < a.rows; i++) {
        for(int j = 0; j < b.cols; j++) {
            m.data[i][j] = 0;
            for(int k = 0; k < a.cols; k++) {
                m.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    return m;
}

int main()
{

    Matrix a = read_matrix();
    display_matrix(a);

    return 0;
}

int ask(char question[])
{
    int res = 0;
    puts(question);
    scanf("%d", &res);
}