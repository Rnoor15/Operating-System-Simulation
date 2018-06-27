#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

class Process {
public:
	Process(int id, int p) : pid_num(id), priority(p) {}
	int getPriority() const {
		return priority;
	}
	int getID() const {
		return pid_num;
	}
	friend ostream &operator<<(ostream &os, const Process &p) {
		os << "Process " << p.pid_num << " Priority " << p.priority;
		return os;
	} 
	friend bool operator==(const Process &p1, const Process &p2) {
		return p1.pid_num == p2.pid_num and p1.priority == p2.priority;
	}

	void setFile(const string &file_name) {
		file = file_name;
	}

	string getFile() const {
		return file;
	}

private:
	int pid_num;
	int priority;
	string file;
};




class Comparator {
public:
	bool operator() (Process &left, Process &right) {
		return left.getPriority() < right.getPriority();
	}
	
};

struct Frame {
	int id;
	int page;
	int time;
	Frame(int name, int num, int tim): id(name), page(num), time(tim) {}
};

int lowestTimeIndex(const vector <Frame> &v) {
	int max = 0;
	for(int i = 0; i < v.size(); i++) {
		if(v[i].time > max) {
			max = v[i].time;
		}
	}

	int min = max;
	int min_index = 0;

	for(int i =0; i < v.size(); i++) {
		if(v[i].time < min) {
			min = v[i].time;
			min_index = i;
		}
	}

	return min_index;
}

void AddFrame(vector <Frame> &v, int pg, int id, int time, int max_size) {
	for(int i = 0; i < v.size(); i++) {
		if(v[i].id == id and v[i].page == pg) {
			v[i].time = time;
			return;
		}
	}
	Frame f(id, pg, time);
	for(int i = 0; i < v.size(); i++) {
		if(v[i].id == -1) {
			v[i].id = id;
			v[i].page = pg;
			v[i].time = time;
			return; 		}
	}
	if(v.size() == max_size) {
		int oldest_frame = lowestTimeIndex(v);
		v[oldest_frame].id = id;
		v[oldest_frame].page = pg;
		v[oldest_frame].time = time;
		return;
	}
	v.push_back(f);
}

int NumWords(const string &command) {
	int count = 0;
	for(int i = 0; i < command.length(); i++) {
		if(command[i] == ' ') {
			count++;
		}
	}

	return count;
}


int main() {
	string mem;
	cout << "How much RAM memory is there for this system?" << endl;
	getline(cin, mem);
	int count =0;
	while(true) {
		if(!isdigit(mem[count])) {
			cout << "Incorrect Input" << endl;
			getline(cin,mem);
			count = 0;
			continue;
		}
		count++;
		if(count == mem.length()) break;
	}

	
	long long int memory = stoi(mem);

	/*cout << "How much RAM memory is there for this system?" << endl;
	cin >> memory;
	while(cin.fail()) {
		cout << "Error: Not Integer. Please Enter Again." << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cin >> memory;

	}
	cin.get();*/

	string pg_size;
	cout << "What is the size of each page?" << endl;
	getline(cin, pg_size);
	count = 0;
	while(true) {
		if(!isdigit(pg_size[count])) {
			cout << "Incorrect Input" << endl;
			getline(cin,pg_size);
			count = 0;
			continue;
		}
		count++;
		if(count == pg_size.length()) break;
	}
	int page_size = stoi(pg_size);

	string disk;
	cout << "How many hard disks does this system have?" << endl;
	getline(cin, disk);
	count = 0;
	while(true) {
		if(!isdigit(disk[count])) {
			cout << "Incorrect Input" << endl;
			getline(cin,disk);
			count = 0;
			continue;
		}
		count++;
		if(count == disk.length()) break;
	}

	int num_disks = stoi(disk);

	long long int num_pages = memory / page_size;

	vector <Frame> memoryVec;

	vector < vector<Process> >  input_output_queue(num_disks);

	vector<Process> cpu_queue;

	int pid = 1;
	int time_stamp = 1;
	string command;

	cout << "Please Enter Any Number of Commands" << endl;
	while (true) {
		getline(cin, command);

		if(command[0] == 'A' and command[1] == ' ' and command.length() > 2) {

			for(int i = 2; i < command.length(); i++) {
				if(!isdigit(command[i])) {
					cout << "Incorrect Command" << endl;
					goto x;
				}
			}

			int priority = stoi(command.substr(2));
			Process p(pid, priority);
			AddFrame(memoryVec, 0, p.getID(), time_stamp, num_pages);

			cpu_queue.push_back(p);
			sort(cpu_queue.begin(), cpu_queue.end(), Comparator());
			pid++;
			time_stamp++;
		}

		else if(command == "t") {
			if(cpu_queue.empty()) {
				cout << "There are no processes to terminate" << endl;
				goto x;
			}
			int id = cpu_queue[cpu_queue.size()-1].getID();
			for(int i = 0; i < memoryVec.size(); i++) {
				if(memoryVec[i].id == id) {
					memoryVec[i].id = -1;
				}
			}
			cpu_queue.pop_back();
		}

		else if(command[0] == 'd' and command[1] == ' ' and command.length() > 2) {

			string disk_num;

			int counter = 2;
			if(command[counter] == ' ') {
				cout << "Incorrect Command" << endl;
				goto x;
			}
			for(int i = 2; command[i] != ' '; i++) {
				if(!isdigit(command[i])) {
					cout << "Incorrect Command" << endl;
					goto x;
				}
				disk_num += command[i];
				counter++;
			}
			counter++;
			string file_name;
			for(int i = counter; i < command.length(); i++) {
				if(command[i] == ' ') {
					cout << "Incorrect Command" << endl;
					goto x;
				}
				file_name += command[i];
			}

			int num = stoi(disk_num);

			if(num >= num_disks) {
				cout << "Hard Disk Does Not Exist" << endl;
				goto x;
			}

			if(cpu_queue.empty()) {
				cout << "There Are No Processes Left" << endl;
				goto x;
			}
			cpu_queue[cpu_queue.size()-1].setFile(file_name);
			input_output_queue[num].push_back(cpu_queue[cpu_queue.size()-1]);
			cpu_queue.pop_back();

		}

		else if(command[0] == 'D' and command[1] == ' ' and command.length() > 2) {

			for(int i = 2; i < command.length(); i++) {
				if(!isdigit(command[i])) {
					cout << "Incorrect Command" << endl;
					goto x;
				}
			}

			int disk_num = stoi(command.substr(2));
			if(disk_num >= num_disks) {
				cout << "Hard Disk Does Not Exist" << endl;
				goto x;
			}
			if(input_output_queue[disk_num].empty()) {
				cout << "The Hard Disk is Empty" << endl;
				goto x;
			}
			cpu_queue.push_back(input_output_queue[disk_num][0]);
			sort(cpu_queue.begin(), cpu_queue.end(), Comparator());
			input_output_queue[disk_num].erase(input_output_queue[disk_num].begin());
		}

		else if(command[0] == 'm' and command[1] == ' ' and command.length() > 2) {

			for(int i = 2; i < command.length(); i++) {
				if(!isdigit(command[i])) {
					cout << "Incorrect Command" << endl;
					goto x;
				}
			}

			if(cpu_queue.empty()) {
				cout << "There Are No Processes In The Queue" << endl;
				goto x;
			}



			int address = stoi(command.substr(2));
			int page_num = address / page_size;
			int id = cpu_queue[cpu_queue.size()-1].getID();
			AddFrame(memoryVec, page_num, id, time_stamp, num_pages);
			time_stamp++;
		}

		else if(command[0] == 'S' and command[1] == ' ' and command[2] == 'r' and command.length() == 3) {

			if(cpu_queue.empty()) {
				cout << "There Are No Processes In The Queue" << endl;
				goto x;
			}
			cout << "Current Process Using CPU: " << cpu_queue[cpu_queue.size()-1] << endl;
			cout << "Processes Waiting in Ready Queue:" << endl;
			for(int i = cpu_queue.size() - 2; i >= 0; i--) {
				cout << cpu_queue[i] << endl;
			}
		}

		else if(command[0] == 'S' and  command[1] == ' ' and command[2] == 'i' and command.length() == 3) {

			if(input_output_queue.empty()) {
				cout << "All Hard Disks Are Empty" << endl;
				goto x;
			}
			for(int i = 0; i < input_output_queue.size(); i++) {
				if(!input_output_queue[i].empty()) {
					cout << "Hard Disk " << i << endl;
					cout << "Current Process: " << input_output_queue[i][0] << " File: " 
						<< input_output_queue[i][0].getFile() << endl;
					cout << "Processes Waiting in Queue:" << endl;
					for(int j = 1; j < input_output_queue[i].size(); j++) {
						cout << input_output_queue[i][j] << " File: " 
							<< input_output_queue[i][j].getFile() << endl;
					}
				}
				else {
					cout << "Hard Disk " << i << " Is Empty" << endl;
				}
			}
		}

		else if(command[0] == 'S' and command[1] == ' ' and command[2] == 'm' and command.length() == 3) {
			int full_count = 0;
			for(int i = 0; i < memoryVec.size(); i++) {
				if(memoryVec[i].id != -1) {
					cout << "Frame " << i << ": Process " << memoryVec[i].id << " Page " 
					<< memoryVec[i].page << " Time: " << memoryVec[i].time << endl;
					full_count++;
				}
			}
			if(full_count == 0) {
				cout << "Frame Table Is Empty" << endl;
			}
		}

		else {
			cout << "Incorrect Command" << endl;
		}
		x:;
	} 



	return 0;
}