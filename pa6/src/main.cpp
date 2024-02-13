#include <iostream>
#include <cstring>
#include <string>

using namespace std;

struct tvseries {
    char *series_name;
    int original_release_year;
    struct tv_episode {
        char episode_name[30];
        int episode_number;
        string episode_release_date;
      };
    struct tv_season {
        int season_number;
        int season_release_year;
        tv_episode episodes[5];
      } seasons[3], *seasons_ptr;

    void staticPrint();
    static void dynamicPrint(const tvseries* series);
} some_tv_series, *ptr_some_tv_series = &some_tv_series;

void tvseries::staticPrint() {
    cout << "Series Name: " << series_name << " (" << original_release_year << ")" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "Season " << seasons[i].season_number << 
            " (" << seasons[i].season_release_year << "):" << endl;
        for (int j = 0; j < 5; j++) {
            cout << "Episode " << seasons[i].episodes[j].episode_number << ": " << 
                seasons[i].episodes[j].episode_name 
                << " (" << seasons[i].episodes[j].episode_release_date << ")" << endl;
        }
    }
}

void tvseries::dynamicPrint(const tvseries* series) {
    cout << "Series Name: " << series->series_name << 
        " (" << series->original_release_year << ")" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "Season " << series->seasons_ptr[i].season_number << 
            " (" << series->seasons_ptr[i].season_release_year << "):" << endl;
        for (int j = 0; j < 5; j++) {
            cout << "Episode " << series->seasons_ptr[i].episodes[j].episode_number << ": " << 
                series->seasons_ptr[i].episodes[j].episode_name 
                << " (" << series->seasons_ptr[i].episodes[j].episode_release_date << ")" << endl;
        }
    }
}

int main() {
    cout << "Static Memory Allocation:" << endl;
    const char* sn = "Mickey Mouse Clubhouse";
    some_tv_series.series_name = new char[strlen(sn) + 1];
    // initialize the series name
    strcpy(some_tv_series.series_name, sn);
    // initialize the original release year
    some_tv_series.original_release_year = 2006;

    // initialize 15 episodes
    tvseries::tv_episode s1e1 = {"Daisy Bo-Peep", 1, "2006-01-01"};
    tvseries::tv_episode s1e2 = {"Mickey Goes Fishing", 2, "2006-02-01"};
    tvseries::tv_episode s1e3 = {"Pluto's Puppy Adventure", 3, "2006-03-01"};
    tvseries::tv_episode s1e4 = {"Daisy in the Sky", 4, "2006-04-01"};
    tvseries::tv_episode s1e5 = {"A Surprise for Minnie", 5, "2006-05-01"};

    tvseries::tv_episode s2e1 = {"Goofy on Mars", 1, "2007-01-01"};
    tvseries::tv_episode s2e2 = {"Mickey's Handy Helpers", 2, "2007-02-01"};
    tvseries::tv_episode s2e3 = {"Goofy Baby", 3, "2007-03-01"};
    tvseries::tv_episode s2e4 = {"Minnie's Picnic", 4, "2007-04-01"};
    tvseries::tv_episode s2e5 = {"Goofy's Bird", 5, "2007-05-01"};

    tvseries::tv_episode s3e1 = {"Mickey's Big Band Concert", 1, "2008-01-01"};
    tvseries::tv_episode s3e2 = {"Goofy's Hat", 2, "2008-02-01"};
    tvseries::tv_episode s3e3 = {"Donald's Hiccups", 3, "2008-03-01"};
    tvseries::tv_episode s3e4 = {"Daisy loses her Bow", 4, "2008-04-01"};
    tvseries::tv_episode s3e5 = {"Mickey's Art Show", 5, "2008-05-01"};

    // initialize the seasons
    tvseries::tv_season season1 = {1, 2006, {s1e1, s1e2, s1e3, s1e4, s1e5}};
    tvseries::tv_season season2 = {2, 2007, {s2e1, s2e2, s2e3, s2e4, s2e5}};
    tvseries::tv_season season3 = {3, 2008, {s3e1, s3e2, s3e3, s3e4, s3e5}};

    // assign the seasons to the series
    some_tv_series.seasons[0] = season1;
    some_tv_series.seasons[1] = season2;
    some_tv_series.seasons[2] = season3;

    // print the series
    some_tv_series.staticPrint();


    cout << endl << "Dynamic Memory Allocation:" << endl;
    const char* sn2 = "The Simpsons";
    ptr_some_tv_series->series_name = new char[strlen(sn2) + 1];
    // initialize the series name
    strcpy(ptr_some_tv_series->series_name, sn2);

    // initialize the original release year
    ptr_some_tv_series->original_release_year = 1989;

    // initialize 3 seasons
    ptr_some_tv_series->seasons_ptr = new tvseries::tv_season[3];
    for (int i = 0; i < 3; i++) {
        ptr_some_tv_series->seasons_ptr[i].season_number = i + 1;
        ptr_some_tv_series->seasons_ptr[i].season_release_year = 1989 + i;

        // initialize 5 episodes for each season
        for (int j = 0; j < 5; j++) {
            ptr_some_tv_series->seasons_ptr[i].episodes[j].episode_number = j + 1;
            ptr_some_tv_series->seasons_ptr[i].episodes[j].episode_release_date = 
                "1989-01-0" + to_string(j + 1);
        }
    }

    // initialize the episode titles
    strcpy(ptr_some_tv_series->seasons_ptr[0].episodes[0].episode_name, 
            "Krusty Gets Busted");
    strcpy(ptr_some_tv_series->seasons_ptr[0].episodes[1].episode_name,
            "Bart the Genius");
    strcpy(ptr_some_tv_series->seasons_ptr[0].episodes[2].episode_name,
            "Homer's Odyssey");
    strcpy(ptr_some_tv_series->seasons_ptr[0].episodes[3].episode_name,
            "There's No Disgrace Like Home");
    strcpy(ptr_some_tv_series->seasons_ptr[0].episodes[4].episode_name,
            "Bart the General");
    
    strcpy(ptr_some_tv_series->seasons_ptr[1].episodes[0].episode_name,
            "Bart Gets an F");
    strcpy(ptr_some_tv_series->seasons_ptr[1].episodes[1].episode_name,
            "Simpson and Delilah");
    strcpy(ptr_some_tv_series->seasons_ptr[1].episodes[2].episode_name,
            "Treehouse of Horror");
    strcpy(ptr_some_tv_series->seasons_ptr[1].episodes[3].episode_name,
            "Three Eyes on Every Fish");
    strcpy(ptr_some_tv_series->seasons_ptr[1].episodes[4].episode_name,
            "Dancin' Homer");

    strcpy(ptr_some_tv_series->seasons_ptr[2].episodes[0].episode_name,
            "Stark Raving Dad");
    strcpy(ptr_some_tv_series->seasons_ptr[2].episodes[1].episode_name,
            "Mr. Lisa Goes to Washington");
    strcpy(ptr_some_tv_series->seasons_ptr[2].episodes[2].episode_name,
            "When Flanders Failed");
    strcpy(ptr_some_tv_series->seasons_ptr[2].episodes[3].episode_name,
            "Are we there yet?");
    strcpy(ptr_some_tv_series->seasons_ptr[2].episodes[4].episode_name,
            "Total Recall");


    // print the series
    tvseries::dynamicPrint(ptr_some_tv_series);

    // deallocate the memory
    // is this needed? runs fine without it
    //delete[] some_tv_series.series_name;
    //delete[] ptr_some_tv_series->seasons_ptr;

    return 0;
}
