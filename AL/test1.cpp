int main(){
	int* test = new int[100];
	for(int i = 0; i < 100; i++){
		if(i == test[i])
			continue;
		else
			break;
	}
}
