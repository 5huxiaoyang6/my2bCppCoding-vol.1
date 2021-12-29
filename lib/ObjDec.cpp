#include<iostream>
#include<string>
#include"lib2b.cpp"
using namespace std;

class CommandHandler{
	
	private:
		string welcome_content = "��ӭʹ����;mini��Ʒ������¼ϵͳ!���ߣ�3200611126��Ц��";
		string help_main = "����ss����?��ð������벻Ҫ©������ķָ�����";
		string help_error1 = "δ֪��ָ�������ss����?��ð���"; 
		string help_menu[6] =
		{"ʹ��'ss_record_��ƷID_��Ʒ����_��Ʒ����_��Ʒ����_��Ʒ�۸�'��д��һ����Ʒ����Ϣ,�벻Ҫ�����а�������,�Լ�ȷ����ȷ�����ͣ����������������ֿ��ܻᵼ�³������",
		"ʹ��'ss_consult_��ƷID'�����һ����Ʒ�ľ�����Ϣ",
		"ʹ��'ss_list'���г����еĲ�Ʒ��Ϣ",
		"ʹ��'ss_insuf_�����ı�����'���г����в��㱨���������Ĳ�Ʒ",
		"ʹ��'ss_category_��������'���г�����ָ�����͵Ĳ�Ʒ", 
		"ʹ��'ss_exit'���˳�ϵͳ"};
		string  exit_content = "��л����ʹ�ã��´��ټ���";
		string msg_list = "Ŀǰ���в�Ʒ���£�";
		int inline_warning_number; 
	public:
		void setWelcomContent(string content);
		//�����ʺ���Ϣ 
		void setInlineWarningNumber(int number);
		void welcome();
		void guide();
		//��ӡ�ʺ���Ϣ 
		void storageWarning(string list[1024][5],int i_m);
		//��澯�� 
		//void commandLoop();
		//ָ��ѭ������
		//void judgeMenuLevel2(string str);
		//�ڶ���ָ���ж� 
		void judgeMenuLevel1(string var_str,string list[1024][5],string list_type[1024][5],int i_m,string path);
		//��һ��ָ���ж� 
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
		//���� ÿһ�����ݼ�¼�Ľṹ�� 
		Data data_base[1024];
		Data data_base_type[1024];
		Data data_base_alert[1024]; 
		string list[1024][5];
		string list_type[1024][5]; 
		//����data_base���� �� ���Ԫ������Ϊ1024 
		void get_current_data(string path);
		/*
		void setPath(string path){
					//�������·�� 
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











