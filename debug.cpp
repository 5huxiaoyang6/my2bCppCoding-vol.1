#include"lib\ObjDef.cpp"
using namespace std;
int main(){
	InitSetter Setter;
	//FileController FC(Setter.get_path());
	CommandHandler CH;
	//---CH初始化---
	CH.welcome();
	cout<<endl;
	CH.setInlineWarningNumber(Setter.get_alert_number());
	CH.storageWarning(Setter.list,Setter.i_m);
	string input_str;
	cout<<endl;
	CH.guide();
	cout<<endl;
	cout<<"欢迎进入查询系统，请随便输入点什么以开始吧！"<<endl;
	while(1){
		Setter.self_update();
		cin>>input_str;
		CH.judgeMenuLevel1(input_str,Setter.list,Setter.list_type,Setter.i_m,Setter.get_path());
	}
}
