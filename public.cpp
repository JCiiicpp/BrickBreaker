#include <iostream>
using namespace std;
int n;
const int N = 16;
int st[N];//�ж�λ�����Ƿ�ѡ��,0��ʾδ���ǣ�1��ʾѡ�У�2��ʾδѡ��
//u��ʾ��ǰѡ���ڼ�����->��Ӧ�������ĵڼ���
void dfs(int u) {
    if (u == n) {
        for (int i = 0; i < n; ++i) {
            if (st[i] == 1) {
                cout << i + 1 << " ";
            }
        }
        cout << endl;
        return; 
    }
    //�������ܳ��ֵķ�֧
    for (int i = 1; i <= 2; ++i) {
        st[u] = i;
        dfs(u + 1);
        //�ָ�
        st[u] = 0;
    }

}

int main2() {
    
    cin >> n;
    dfs(0);
    return 0;
}
