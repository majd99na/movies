#include <iostream>
#include <fstream>
#include "vector"
#include "string.h"
using namespace std;
class MoviesDB{
private:
    int i,count=0,Scount=0;
    vector<int>found;
    bool Top=false;
    struct MoviesINFO {
        string name,genre,director,duration,Ryear,plot,rate;
    };
    vector<MoviesINFO>Movies;
    int listmovies=0;
public:
        void MainMenu(){
            int c=0;
            cout<<endl<<"1.List All Movies in DB\n2.Search for a movie\n3.Filter"<<endl;
            cin>>c;
            cin.clear();
            cin.ignore();
            switch (c) {
                case 1:
                    MoviesList();
                    MainMenu();
                case 2:
                    Search();
                    MainMenu();
                case 3:
                    Filter();
                default:
                    MainMenu();
                    break;
            }
        }
        void Search()
        {
            int c;
            cout<<"What are you searching for?\n1.Movie's Title\n2.Genre\n3.Director\n4.Plot"<<endl;
            cin>>c;
            i,count=0,Scount=0;
            string keyword,taken;
            string temp;
            string D;
            found.clear();
            size_t pos;
            cout<<"Please enter a search keyword"<<endl;
            cin.ignore();
            std::getline(std::cin,keyword);
            for(i=0;i<Movies.size();i++)
            {
                if(c==1) {
                    temp = Movies[i].name;
                    D = " ";
                }
                else if(c==2) {
                    temp = Movies[i].genre;
                    D = "/";
                }
                else if(c==3){
                    temp = Movies[i].director;
                    D=" ";
                }
                else if(c==4){
                    temp = Movies[i].plot;
                    D=" ";
                }
                if(keyword==temp){
                    count++;
                    found.push_back(i);
                    break;
                }
                while(((pos=temp.find(D))!=string::npos))
                {
                            taken=temp.substr(0,pos);
                            temp.erase(0,pos+D.length());
                            if(keyword==taken)
                            {
                                found.push_back(i);
                                count++;
                                break;
                            }
                            if(keyword==temp)
                            {
                                found.push_back(i);
                                count++;
                                break;
                            }
                }
            }
            if(count>0) {
                if(count==1)
                        cout << "{---- Found Only 1 Result ----}" << endl;
                else
                        cout << "{---- Found " << count << " Results ----}" << endl << "==================="
                                                                                   "=====================" << endl;
                Display();
                if(count==1)
                    cout<<"{---- Found Only 1 Result ----}"<<endl;
                else
                    cout<<"{---- Found "<<count<<" Results ----}"<<endl;
            }
            else if(count==0) {
            for (int m = 0; m < Movies.size(); m++)
            {
                if (c - 1 == 0) {
                    temp = Movies[m].name;
                    D = " ";
                }
                else if (c - 1 == 1) {
                    temp = Movies[m].genre;
                    D = "/";
                }
                else if (c - 1 == 2) {
                    temp = Movies[m].director;
                    D = " ";
                }
                if ((temp.find(keyword)) != string::npos) {
                    Scount++;
                    found.push_back(m);
                        }

                  }
            }
            if(Scount>0)
             {
            cout << "!!!!!!!!! Your search was not found , here are similar results !!!!!!!!!" << endl;
                Display();
             }
            else if(count==0&&Scount==0)
            cout<<"NOT FOUND! TRY AGAIN"<<endl;
            system("pause");
        }
        void Display(){
            for (int j = 0; j < count || j<Scount; j++)
                cout << j + 1 << "." << "Name: " << Movies[found.at(j)].name << endl << "Genre: "
                     << Movies[found.at(j)].genre << endl
                     << "Rate: " << Movies[found.at(j)].rate << endl << "Director: "
                     << Movies[found.at(j)].director << endl
                     << "Duration: " << Movies[found.at(j)].duration << endl << "Releasing Year: "
                     << Movies[found.at(j)].Ryear << endl
                     << "Plot: " << Movies[found.at(j)].plot << endl << "================"
                                                                           "========================" << endl;
        }
        void Filter(){
            int c;
            cout<<"1.By Rate/Descending\n2.By Rate/Ascending \n3.By Genre\n4. Top 10 Movies"<<endl;
            cin>>c;
            switch (c) {
                case 1:
                    FilterByRate_Descending();
                    MainMenu();
                case 2:
                    FilterByRate_Ascending();
                    MainMenu();
                case 3:
                    FilterByGenre();
                    MainMenu();
                case 4:
                    Top=true;
                    FilterByRate_Descending();
                default:
                    MainMenu();
            }
        }
        void FilterByRate_Descending(){
            vector<string>ByRateName;
            vector<double>ByRateRate;
            bool IsSorted;
            for(int i=0;i<Movies.size();i++){
                    ByRateName.push_back(Movies[i].name);
                    ByRateRate.push_back(stod(Movies[i].rate));
                }
            for(int j=0;j<Movies.size();j++){
                IsSorted=true;
                for(int m=1;m<100-j;m++){
                    if(ByRateRate[m]>ByRateRate[m-1]){
                        double temp;
                        string temp1;
                        temp=ByRateRate[m];
                        ByRateRate[m]=ByRateRate[m-1];
                        ByRateRate[m-1]=temp;
                        temp1=ByRateName[m];
                        ByRateName[m]=ByRateName[m-1];
                        ByRateName[m-1]=temp1;
                        IsSorted= false;
                    }
                }
                if(IsSorted) break;
            }
            if(!Top)
            for(int k=0;k<100;k++)
                cout <<k+1<<"."<< ByRateName[k] << " , Rating: " << ByRateRate[k] <<endl<<
                "========================================"<<endl;
            else
            for(int k=0;k<10;k++)
                    cout <<k+1<<"."<< ByRateName[k] << " , Rating: " << ByRateRate[k] <<endl<<
                         "========================================"<<endl;
            Top=false;
            ByRateRate.clear();
            ByRateName.clear();
            system("Pause");
        }
        void FilterByRate_Ascending(){
        vector<string>ByRateName;
        vector<double>ByRateRate;
        bool IsSorted;
        for(int i=0;i<Movies.size();i++){
            ByRateName.push_back(Movies[i].name);
            ByRateRate.push_back(stod(Movies[i].rate));
        }
        for(int j=0;j<Movies.size();j++){
            IsSorted=true;
            for(int m=1;m<Movies.size()-j;m++){
                if(ByRateRate[m]<ByRateRate[m-1]){
                    double temp;
                    string temp1;
                    temp=ByRateRate[m];
                    ByRateRate[m]=ByRateRate[m-1];
                    ByRateRate[m-1]=temp;
                    temp1=ByRateName[m];
                    ByRateName[m]=ByRateName[m-1];
                    ByRateName[m-1]=temp1;
                    IsSorted= false;
                }
            }
            if(IsSorted) break;
        }
        for(int k=0;k<100;k++)
                cout <<k+1<<"."<< ByRateName[k] << " , Rating: " << ByRateRate[k] <<endl<<
                     "========================================"<<endl;
        ByRateRate.clear();
        ByRateName.clear();
        system("pause");
    }
        void FilterByGenre(){
            cout<<"Choose a genre"<<endl<<"1.Action\n2.Horror\n3.Drama\n4.Romance\n5.Sci-Fi\n6.Thriller\n7.Comedy\n8.Musical\n9.Animation\n10.Crime\n11.Fantasy"
                                          "\n12.War\n13.Adventure\n14.Music\n15.Mystery\n16.History\n17.Biography"<<endl;
            int m;
            string genre;
            vector<string>genres={"Action","Horror","Drama","Romance","Sci-Fi","Thriller","Comedy","Musical","Animation","Crime","Fantasy"
            ,"War","Adventure","Music","Mystery","History","Biography"};
            cin.ignore();
            cin>>m;
            switch (m) {
                case 1:
                    genre=genres.at(0);
                    break;
                case 2:
                    genre=genres.at(1);
                    break;
                case 3:
                    genre=genres.at(2);
                    break;
                case 4:
                    genre=genres.at(3);
                    break;
                case 5:
                    genre=genres.at(4);
                    break;
                case 6:
                    genre=genres.at(5);
                    break;
                case 7:
                    genre=genres.at(6);
                    break;
                case 8:
                    genre=genres.at(7);
                    break;
                case 9:
                    genre=genres.at(8);
                    break;
                case 10:
                    genre=genres.at(9);
                    break;
                case 11:
                    genre=genres.at(10);
                    break;
                case 12:
                    genre=genres.at(11);
                    break;
                case 13:
                    genre=genres.at(12);
                    break;
                case 14:
                    genre=genres.at(13);
                    break;
                case 15:
                    genre=genres.at(14);
                    break;
                case 16:
                    genre=genres.at(15);
                    break;
                case 17:
                    genre=genres.at(16);
                    break;
                default:
                    Filter();
            }
            int count=0;
            vector<int>indexes;
            string temp,taken;
            size_t pos = 0;
            string Delimiter="/";
            for(int i=0;i<Movies.size();i++){
                temp=Movies[i].genre;
                while ((pos=temp.find(Delimiter))!=string::npos) {
                    taken=temp.substr(0,pos);
                    if(genre==taken){
                        count++;
                        indexes.push_back(i);
                    }
                    temp.erase(0,pos+Delimiter.length());
                    if(genre==temp){
                        count++;
                        indexes.push_back(i);
                    }
                }
            }
            if(count>1)
            cout<<"----"<<genre<<" Movies---- "<<count<<" Movies"<<endl;
            else if(count==0)
                cout<<"Sorry, there's no movies in this genre"<<endl;
            else
            cout<<"----"<<genre<<" Movies---- "<<"There's only one Movie in this genre"<<endl;
            for(int j=0;j<count;j++)
                cout << j+1 << "." << Movies[indexes.at(j)].name << "      Rating: " << Movies[indexes.at(j)].rate << endl
                <<"========================================"<<endl;
            if(count>1)
                cout<<"----"<<genre<<" Movies---- "<<count<<" Movies"<<endl;
            else if(count==0)
                cout<<"Sorry, there's no movies in this genre"<<endl;
            system("pause");
        }
        void MoviesList() {
            for (int i = 0; i < Movies.size(); i++)
                    cout << endl << i + 1 << "." << Movies[i].name << endl << endl
                         << "========================================" << endl;
                    cout << "There is " << Movies.size() << " Movies in the database currently" << endl << endl;
                    cout << "You can choose a movie by number to show information about , just type the "
                            "movie's list number and press enter / type 0 to go back to the main menu" << endl;
                cin>>listmovies;
                if(listmovies==0) MainMenu();
                else
                    cout << endl << listmovies << "." << "Name: " << Movies[listmovies - 1].name << endl << "Genre: "
                         << Movies[listmovies - 1].genre << endl
                         << "Rate: " << Movies[listmovies - 1].rate << endl << "Director: "
                         << Movies[listmovies - 1].director << endl
                         << "Duration: " << Movies[listmovies - 1].duration << endl << "Releasing Year: "
                         << Movies[listmovies - 1].Ryear << endl
                         << "Plot: " << Movies[listmovies - 1].plot << endl << "================"
                                                                             "========================" << endl;
        }
        void ReadDB() {
            ifstream input;
            input.open("Database.txt");
            size_t pos = 0;
            string taken, TEXT;
            string Delimiter = "?";
            int NUM = 0, i = 0;
            while (getline(input, TEXT)) {
                i=0;
                if (TEXT==" ")continue;
                Movies.push_back({"", "", "", "", "", "", ""});
                while ((pos = TEXT.find(Delimiter)) != std::string::npos) {
                    taken = TEXT.substr(0, pos);
                    if (i == 0)
                        Movies[NUM].name = taken;
                    else if (i == 1)
                        Movies[NUM].rate = taken;
                    else if (i == 2)
                        Movies[NUM].genre = taken;
                    else if (i == 3)
                        Movies[NUM].director = taken;
                    else if (i == 4)
                        Movies[NUM].duration = taken;
                    else if (i == 5)
                        Movies[NUM].Ryear = taken;
                    else if (i == 6)
                        Movies[NUM].plot = taken;
                    TEXT.erase(0, pos + Delimiter.length());
                    i++;
                }
                NUM++;
            }
            input.close();
        }
};
int main() {
     MoviesDB moviesDb;
     moviesDb.ReadDB();
     moviesDb.MainMenu();
    return 0;
}
