#include<iostream>
#include<string>
#include"ObjDec.cpp"
using namespace std;
void InitSetter::load_index(){
	/*
	���ڼ���index 
	*/
	int i_m =  getHowManyFilesInDir(path);
	int i=0;
	string content;
	for(;i<i_m;i++){
		content = getNameOfIndexFile(i,path);
		data_base[i].index = content.substr(0,content.length()-4);
	}
}
void InitSetter::type_sorting(){
	int i_m = getHowManyFilesInDir(path);
	Data temp;
	for(int i=0;i<i_m;i++){
		data_base_type[i]=data_base[i];
	}
	//���Ƚ����鸴��һ��
	
	int start_index = 0;
	while(start_index<i_m-1){
	for(int i=start_index+1;i<i_m;i++){
		//�ӵ�һ����ʼ���ң�����ҵ�һ���ģ��Ͱɺ�һ���Ͳ�ͬ���Ǹ�����
		if(data_base_type[start_index].type==data_base_type[i].type){
			temp = data_base_type[start_index+1];
			data_base_type[start_index+1] = data_base_type[i];
			data_base_type[i] = temp;
			//����
			start_index += 1;
			//�������� ��ʼ���ҵ� 
			} 
		}
	}
}
void InitSetter::alert_sorting(){
	int i_m = getHowManyFilesInDir(path);
	int a=0; 
	for(int i=0;i<i_m;i++){
		if(data_base[i].amount<alertNumber){
			data_base_alert[a]=data_base[i];
			a++;
		}
	}
	amount_in_alert = a+1;
}


void InitSetter::get_current_data(string relative_path){
	/*
	@path string
	##��update data_base
	������Ҫ��load_index 
	*/
	load_index(); 
	int i_m = getHowManyFilesInDir(relative_path);
	int i=0;
	int second_loop_index[4];
	string content;
	//�������������Լ������������� 
	for(;i<i_m;i++){
		content = getFileContent(relative_path,data_base[i].index,".csv");
		//�洢�ļ������� ��index 
		for(int i1=0;i1<3;i1++){
				if(i1 == 0 ){
					second_loop_index[i1] = content.find(',');
				}else{
				second_loop_index[i1] = content.find(',',second_loop_index[i1-1]+1);
		}
	} 
	//��� ָ���ļ��ж��ŵ�λ�� 
	//��ʱ second_loop_index[3] ���������� 
	data_base[i].name = content.substr(0,second_loop_index[0]);
	//��0����һ������λ��Ϊ name 
	data_base[i].type = content.substr(second_loop_index[0]+1,second_loop_index[1]-second_loop_index[0]-1);
	//�ӵ�һ�����ŵ��ڶ������� Ϊ type
	data_base[i].amount = stoi(content.substr(second_loop_index[1]+1,second_loop_index[2]-second_loop_index[1]-1)); 
	//������Ϊ amount
	data_base[i].price = stof(content.substr(second_loop_index[2]+1,content.length()-1)); 
	//... Ϊ price 
	//cout<<data_base[i].price<<endl;������ 
	}
}


void CommandHandler::setWelcomContent(string content){
		this->welcome_content = content;
		//�����µĻ�ӭ���� 
	}
void CommandHandler::welcome(){
	cout<<this->welcome_content<<endl;
	//�����̨��ӡ��ӭ���� 
}
void CommandHandler::judgeMenuLevel1(string var_str,string list[1024][5],string list_type[1024][5],int i_m,string path){
	int i;
	//�������� 
	int v_size = sizeof(this->help_menu)/sizeof(this->help_menu[0]);
	//������鳤�� 
	if(var_str.substr(0,7)=="ss_list"){
		cout<<msg_list<<endl; 
		commandList(list,i_m); 
		//cout<<var_str.substr(0,7)<<endl;
	}else if(var_str.substr(0,7)=="ss_exit"){
			cout<<exit_content<<endl; 
			exit(0);
		//�˳����� 
	}
	else if(var_str.substr(0,8)=="ss_insuf"){
		this->commandInsuf(var_str,list,i_m);
		//ִ�� ����ľ��� 
	}else if(var_str.substr(0,9)=="ss_record"){
			this->commandRecord(var_str,path);
		//ִ�� ��¼ 
	}else if(var_str.substr(0,10)=="ss_consult"){
			this->commandConsult(var_str,list,i_m);
		//ִ�� ��ѯ 
	}else if(var_str.substr(0,11)=="ss_category"){
		this->commandCategory(var_str,list,i_m);
		//ִ�� ���� 
	}else if((var_str.substr(0,2)=="ss")||(var_str.substr(0,1)=="?")){
			for(i=0;i<v_size;i++){
				cout<<this->help_menu[i]<<endl;
			}
		//����ƥ���κβ��� �� ��ͷ��ss ʱ������ʾ 
	}else{
		cout<<this->help_error1<<endl;
		//����ͷ��Ϊssʱ�������� 
	}
}
void InitSetter::self_update(){
		i_m = getHowManyFilesInDir(path);
		get_current_data(path);
		//type_sorting();
		alert_sorting();
		make_list();
		make_list_type();
}
void InitSetter::make_list(){
	int i_m = getHowManyFilesInDir(path);
	for(int i=0;i<i_m;i++){
		list[i][0]=data_base[i].index;
		list[i][1]=data_base[i].name;
		list[i][2]=data_base[i].type;
		list[i][3]=to_string(data_base[i].amount);
		list[i][4]=to_string(data_base[i].price);
	}
}
void InitSetter::make_list_type(){
	int i_m = getHowManyFilesInDir(path);
	for(int i=0;i<i_m;i++){
		list_type[i][0]=data_base_type[i].index;
		list_type[i][1]=data_base_type[i].name;
		list_type[i][2]=data_base_type[i].type;
		list_type[i][3]=to_string(data_base_type[i].amount);
		list_type[i][4]=to_string(data_base_type[i].price);
	}
}
void CommandHandler::commandList(string list[1024][5],int i_m){
	//��ӡ�б���Ϣ 
	for(int i=0;i<i_m;i++){
		cout<<"index:"<<list[i][0]<<"   "<<"name:"<<list[i][1]<<"   "<<"type:"<<list[i][2]<<"   "<<"amount:"<<list[i][3]<<"   "<<"price:"<<list[i][4]<<endl;
		
	}
}

void CommandHandler::commandConsult(string input_str,string list[1024][5],int i_m){
	//�ָ��ı��� ������һ��_ ��λ��
	int last__index;
	for(int i=0;i<(int)input_str.length();i++){
		if(input_str[i]=='_'){
			last__index = i;
		}
	}
	//��ȡҪ��ѯ��ID
	string consult_index = input_str.substr(last__index+1);
	
	//���б���ѯ 
	cout<<"����ѯ��ID�Ĳ�Ʒ����(������Ϣ���޲�Ʒ)��"<<endl;
	
	for(int i=0;i<i_m;i++){
		if(list[i][0]==consult_index){
			cout<<"index:"<<list[i][0]<<"   "<<"name:"<<list[i][1]<<"   "<<"type:"<<list[i][2]<<"   "<<"amount:"<<list[i][3]<<"   "<<"price:"<<list[i][4]<<endl;
		}
	} 
	cout<<"��ѯ��ϣ�"<<endl;
}
void CommandHandler::commandCategory(string input_str,string list_type[1024][5],int i_m){
	//�ָ��ı��� ������һ��_ ��λ��
	int last__index;
	for(int i=0;i<(int)input_str.length();i++){
		if(input_str[i]=='_'){
			last__index = i;
		}
	}
	//��ȡҪ��ѯ������ 
	string consult_index = input_str.substr(last__index+1);
	//cout<<consult_index<<endl;
	//��ѯ 
/*
	int type_index[1024][1024];
	int type_index_i = 0;
	int type_amount[1024];
	int type_amount_i = 0;
	int start_step = 0;
	int b;
	for(int i=0;i<i_m;i++){
		if(list_type[i][3]!=list_type[i+1][3]){
			for(b=start_step;b<=i;b++){
				type_index[type_index_i][b] = b;
			}
			type_amount[type_amount_i]= b - start_step;
			type_index_i++;
		}
		start_step=i+1;
	}*/
	//type_indexΪ��ͬ�����͵�index
	//type_amountΪtype_index��һ�������Ӧ��Ԫ������
	//������Ա���ʱ֮�� 
	cout<<"��"<<"  "<<consult_index<<"  "<<"��ѯ�Ľ������(���������������������)��"<<endl;
	int total_amount = 0;
	for(int i=0;i<i_m;i++){
		
		if(list_type[i][2]==consult_index){
			cout<<"index:"<<list_type[i][0]<<"   "<<"name:"<<list_type[i][1]<<"   "<<"type:"<<list_type[i][2]<<"   "<<"amount:"<<list_type[i][3]<<"   "<<"price:"<<list_type[i][4]<<endl;
			total_amount += stoi(list_type[i][3]);
		} 
	} 
	cout<<"�÷�����һ����"<<total_amount<<"����Ʒ"<<endl;
	cout<<"��ѯ��ϣ�"<<endl; 
}
void CommandHandler::commandInsuf(string input_str,string list[1024][5],int i_m){
	//�ָ��ı��� ������һ��_ ��λ��
	int last__index;
	for(int i=0;i<(int)input_str.length();i++){
		if(input_str[i]=='_'){
			last__index = i;
		}
	}
	//��ȡҪ��ѯ������ 
	int warning_number = stoi(input_str.substr(last__index+1));
	
	cout<<"����"<<"  "<<warning_number<<"  "<<"����Ŀ��(�����������޵���ָ��������Ʒ)��"<<endl; 
	for(int i=0;i<i_m;i++){
		if(stoi(list[i][3])<warning_number){
			cout<<"index:"<<list[i][0]<<"   "<<"name:"<<list[i][1]<<"   "<<"type:"<<list[i][2]<<"   "<<"amount:"<<list[i][3]<<"   "<<"price:"<<list[i][4]<<endl;
		}
	}
	cout<<"��ѯ��ϣ�"<<endl; 
} 
void CommandHandler::setInlineWarningNumber(int number){
	inline_warning_number = number;
}

void CommandHandler::storageWarning(string list[1024][5],int i_m){
	cout<<"Ŀǰ�����������"<<inline_warning_number<<"����Ŀ��(���������޵��ڸ���ֵ����Ŀ)��" <<endl;
	for(int i=0;i<i_m;i++){
		if(stoi(list[i][3])<inline_warning_number){
			cout<<"index:"<<list[i][0]<<"   "<<"name:"<<list[i][1]<<"   "<<"type:"<<list[i][2]<<"   "<<"amount:"<<list[i][3]<<"   "<<"price:"<<list[i][4]<<endl;
		}
	}
}




int CommandHandler::commandRecord(string input_str,string path){
	//�ָ��ַ���

	string original = input_str.substr(10);
	// Ŀǰֻʣ�� �� ID_����_����_����_�۸�

	string index = original.substr(0,original.find('_'));
	original = original.substr(original.find('_')+1);
	string name = original.substr(0,original.find('_'));
	original = original.substr(original.find('_')+1);
	string type = original.substr(0,original.find('_'));
	original = original.substr(original.find('_')+1);
	string amount = original.substr(0,original.find('_'));
	original = original.substr(original.find('_')+1);
	string price = original.substr(0,original.find('_'));

	//TODO:�ų�����ĸ�ʽ 
	
	string info[4]={name,type,amount,price}; 
	string record = string_array_to_record(info,4);
	
	writeFile(path,index,".csv",record);
	cout<<"�ѳɹ���¼�ļ���"<<endl; 
	return 0;	
}

void CommandHandler::guide(){
	cout<<help_main<<endl;
}








