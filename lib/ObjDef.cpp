#include<iostream>
#include<string>
#include"ObjDec.cpp"
using namespace std;
void InitSetter::load_index(){
	/*
	用于加载index 
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
	//首先将数组复制一份
	
	int start_index = 0;
	while(start_index<i_m-1){
	for(int i=start_index+1;i<i_m;i++){
		//从第一个开始查找，如果找到一样的，就吧后一个和不同的那个交换
		if(data_base_type[start_index].type==data_base_type[i].type){
			temp = data_base_type[start_index+1];
			data_base_type[start_index+1] = data_base_type[i];
			data_base_type[i] = temp;
			//交换
			start_index += 1;
			//重新设置 开始查找点 
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
	##能update data_base
	！！需要先load_index 
	*/
	load_index(); 
	int i_m = getHowManyFilesInDir(relative_path);
	int i=0;
	int second_loop_index[4];
	string content;
	//创建迭代变量以及迭代变量上限 
	for(;i<i_m;i++){
		content = getFileContent(relative_path,data_base[i].index,".csv");
		//存储文件的名称 即index 
		for(int i1=0;i1<3;i1++){
				if(i1 == 0 ){
					second_loop_index[i1] = content.find(',');
				}else{
				second_loop_index[i1] = content.find(',',second_loop_index[i1-1]+1);
		}
	} 
	//获得 指定文件中逗号的位置 
	//此时 second_loop_index[3] 数组已填满 
	data_base[i].name = content.substr(0,second_loop_index[0]);
	//从0到第一个逗号位置为 name 
	data_base[i].type = content.substr(second_loop_index[0]+1,second_loop_index[1]-second_loop_index[0]-1);
	//从第一个逗号到第二个逗号 为 type
	data_base[i].amount = stoi(content.substr(second_loop_index[1]+1,second_loop_index[2]-second_loop_index[1]-1)); 
	//。。。为 amount
	data_base[i].price = stof(content.substr(second_loop_index[2]+1,content.length()-1)); 
	//... 为 price 
	//cout<<data_base[i].price<<endl;测试用 
	}
}


void CommandHandler::setWelcomContent(string content){
		this->welcome_content = content;
		//设置新的欢迎文字 
	}
void CommandHandler::welcome(){
	cout<<this->welcome_content<<endl;
	//向控制台打印欢迎文字 
}
void CommandHandler::judgeMenuLevel1(string var_str,string list[1024][5],string list_type[1024][5],int i_m,string path){
	int i;
	//迭代变量 
	int v_size = sizeof(this->help_menu)/sizeof(this->help_menu[0]);
	//获得数组长度 
	if(var_str.substr(0,7)=="ss_list"){
		cout<<msg_list<<endl; 
		commandList(list,i_m); 
		//cout<<var_str.substr(0,7)<<endl;
	}else if(var_str.substr(0,7)=="ss_exit"){
			cout<<exit_content<<endl; 
			exit(0);
		//退出程序 
	}
	else if(var_str.substr(0,8)=="ss_insuf"){
		this->commandInsuf(var_str,list,i_m);
		//执行 不足的警告 
	}else if(var_str.substr(0,9)=="ss_record"){
			this->commandRecord(var_str,path);
		//执行 记录 
	}else if(var_str.substr(0,10)=="ss_consult"){
			this->commandConsult(var_str,list,i_m);
		//执行 查询 
	}else if(var_str.substr(0,11)=="ss_category"){
		this->commandCategory(var_str,list,i_m);
		//执行 分类 
	}else if((var_str.substr(0,2)=="ss")||(var_str.substr(0,1)=="?")){
			for(i=0;i<v_size;i++){
				cout<<this->help_menu[i]<<endl;
			}
		//当不匹配任何操作 且 开头以ss 时发出提示 
	}else{
		cout<<this->help_error1<<endl;
		//当开头不为ss时发出报错 
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
	//打印列表信息 
	for(int i=0;i<i_m;i++){
		cout<<"index:"<<list[i][0]<<"   "<<"name:"<<list[i][1]<<"   "<<"type:"<<list[i][2]<<"   "<<"amount:"<<list[i][3]<<"   "<<"price:"<<list[i][4]<<endl;
		
	}
}

void CommandHandler::commandConsult(string input_str,string list[1024][5],int i_m){
	//分割文本段 获得最后一个_ 的位置
	int last__index;
	for(int i=0;i<(int)input_str.length();i++){
		if(input_str[i]=='_'){
			last__index = i;
		}
	}
	//截取要查询的ID
	string consult_index = input_str.substr(last__index+1);
	
	//对列表轮询 
	cout<<"您查询的ID的产品如下(若无信息则无产品)："<<endl;
	
	for(int i=0;i<i_m;i++){
		if(list[i][0]==consult_index){
			cout<<"index:"<<list[i][0]<<"   "<<"name:"<<list[i][1]<<"   "<<"type:"<<list[i][2]<<"   "<<"amount:"<<list[i][3]<<"   "<<"price:"<<list[i][4]<<endl;
		}
	} 
	cout<<"查询完毕！"<<endl;
}
void CommandHandler::commandCategory(string input_str,string list_type[1024][5],int i_m){
	//分割文本段 获得最后一个_ 的位置
	int last__index;
	for(int i=0;i<(int)input_str.length();i++){
		if(input_str[i]=='_'){
			last__index = i;
		}
	}
	//截取要查询的类型 
	string consult_index = input_str.substr(last__index+1);
	//cout<<consult_index<<endl;
	//查询 
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
	//type_index为有同样类型的index
	//type_amount为type_index第一层数组对应的元素数量
	//上面的以备不时之需 
	cout<<"按"<<"  "<<consult_index<<"  "<<"查询的结果如下(若无数据则该类型无内容)："<<endl;
	int total_amount = 0;
	for(int i=0;i<i_m;i++){
		
		if(list_type[i][2]==consult_index){
			cout<<"index:"<<list_type[i][0]<<"   "<<"name:"<<list_type[i][1]<<"   "<<"type:"<<list_type[i][2]<<"   "<<"amount:"<<list_type[i][3]<<"   "<<"price:"<<list_type[i][4]<<endl;
			total_amount += stoi(list_type[i][3]);
		} 
	} 
	cout<<"该分类中一共有"<<total_amount<<"个产品"<<endl;
	cout<<"查询完毕！"<<endl; 
}
void CommandHandler::commandInsuf(string input_str,string list[1024][5],int i_m){
	//分割文本段 获得最后一个_ 的位置
	int last__index;
	for(int i=0;i<(int)input_str.length();i++){
		if(input_str[i]=='_'){
			last__index = i;
		}
	}
	//截取要查询的类型 
	int warning_number = stoi(input_str.substr(last__index+1));
	
	cout<<"不足"<<"  "<<warning_number<<"  "<<"的项目有(若无数据则无低于指定数量产品)："<<endl; 
	for(int i=0;i<i_m;i++){
		if(stoi(list[i][3])<warning_number){
			cout<<"index:"<<list[i][0]<<"   "<<"name:"<<list[i][1]<<"   "<<"type:"<<list[i][2]<<"   "<<"amount:"<<list[i][3]<<"   "<<"price:"<<list[i][4]<<endl;
		}
	}
	cout<<"查询完毕！"<<endl; 
} 
void CommandHandler::setInlineWarningNumber(int number){
	inline_warning_number = number;
}

void CommandHandler::storageWarning(string list[1024][5],int i_m){
	cout<<"目前库存数量低于"<<inline_warning_number<<"的项目有(无数据则无低于该数值的项目)：" <<endl;
	for(int i=0;i<i_m;i++){
		if(stoi(list[i][3])<inline_warning_number){
			cout<<"index:"<<list[i][0]<<"   "<<"name:"<<list[i][1]<<"   "<<"type:"<<list[i][2]<<"   "<<"amount:"<<list[i][3]<<"   "<<"price:"<<list[i][4]<<endl;
		}
	}
}




int CommandHandler::commandRecord(string input_str,string path){
	//分割字符串

	string original = input_str.substr(10);
	// 目前只剩下 ： ID_名字_类型_数量_价格

	string index = original.substr(0,original.find('_'));
	original = original.substr(original.find('_')+1);
	string name = original.substr(0,original.find('_'));
	original = original.substr(original.find('_')+1);
	string type = original.substr(0,original.find('_'));
	original = original.substr(original.find('_')+1);
	string amount = original.substr(0,original.find('_'));
	original = original.substr(original.find('_')+1);
	string price = original.substr(0,original.find('_'));

	//TODO:排除错误的格式 
	
	string info[4]={name,type,amount,price}; 
	string record = string_array_to_record(info,4);
	
	writeFile(path,index,".csv",record);
	cout<<"已成功记录文件！"<<endl; 
	return 0;	
}

void CommandHandler::guide(){
	cout<<help_main<<endl;
}








