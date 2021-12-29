#include<iostream>
#include<string>
#include"lib2b.cpp"
using namespace std;

class CommandHandler{
	
	private:
		string welcome_content = "欢迎使用迷途mini产品辅助记录系统!作者：3200611126胡笑阳";
		string help_main = "输入ss或者?获得帮助，请不要漏下特殊的分隔符号";
		string help_error1 = "未知的指令，请输入ss或者?获得帮助"; 
		string help_menu[6] =
		{"使用'ss_record_产品ID_产品名称_产品类型_产品数量_产品价格'来写入一个产品的信息,请不要在其中包含逗号,以及确定正确的类型，在数字中输入文字可能会导致程序崩溃",
		"使用'ss_consult_产品ID'来获得一个产品的具体信息",
		"使用'ss_list'来列出所有的产品信息",
		"使用'ss_insuf_数量的报警线'来列出所有不足报警线数量的产品",
		"使用'ss_category_类型名称'来列出所有指定类型的产品", 
		"使用'ss_exit'以退出系统"};
		string  exit_content = "感谢您的使用，下次再见。";
		string msg_list = "目前所有产品如下：";
		int inline_warning_number; 
	public:
		void setWelcomContent(string content);
		//设置问候信息 
		void setInlineWarningNumber(int number);
		void welcome();
		void guide();
		//打印问候信息 
		void storageWarning(string list[1024][5],int i_m);
		//库存警告 
		//void commandLoop();
		//指令循环部分
		//void judgeMenuLevel2(string str);
		//第二层指令判断 
		void judgeMenuLevel1(string var_str,string list[1024][5],string list_type[1024][5],int i_m,string path);
		//第一层指令判断 
		int commandRecord(string input_str,string path); 
		void commandConsult(string input_str,string list[1024][5],int i_m);
		void commandList(string list[1024][5],int i_m);
		void commandInsuf(string input_str,string list[1024][5],int i_m);
		void commandCategory(string input_str,string list_type[1024][5],int i_m); 

		// exit();
		CommandHandler(){

		} 	
	
}; 

/*

class FileController{
	private:
		string path;
	public:
		void set_path(string path){
			path = path;
		}
		void make_list_content();
	FileController(string path){
		set_path(path);	
	}	
};
*/

class InitSetter{
	private:

		string path;
	
		int alertNumber = 50;
		
		int amount_in_alert;
		
		//void import_from_file(); 
		//void make_a_data(string index,string name,string type,int amount,float price);
		void load_index();
		void type_sorting(); 
		void alert_sorting();
	public:
		int i_m;
		struct Data{
			string index,name,type;
			int amount;
			float price;
		};
		//建立 每一个数据记录的结构体 
		Data data_base[1024];
		Data data_base_type[1024];
		Data data_base_alert[1024]; 
		string list[1024][5];
		string list_type[1024][5]; 
		//设置data_base数组 且 最大元素数量为1024 
		void get_current_data(string path);
		/*
		void setPath(string path){
					//设置相对路径 
					this->path = path;
				}
		*/
		/*
		void set_alert_number(int number){
					alertNumber = number;
				}
		*/
		string get_path(){
			return this->path;
		}
		int get_alert_number(){
			return alertNumber;
		}
		/*
		void testoutput(){
					int i=0;
					cout<<"index:"+data_base[i].index<<endl;
					cout<<"name:"+data_base[i].name<<endl;
					cout<<"type:"+data_base[i].type<<endl;
					cout<<"amount:"<<data_base[i].amount<<endl;
					cout<<"price:"<<data_base[i].price<<endl;
				}
		*/
		void make_list();
		void make_list_type();
		void self_update();
	InitSetter(){
		path = "database";
		self_update();
	}


};











