#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <iostream>
#include <string>
#include <fstream> 
#include <vector>

using namespace std;

// ����������� ����� ��� �����
class Media {
public:
    virtual void playSong() = 0; // ����� ����������� �������
    virtual ~Media() {} // ����������� ����������
};

// ����� ��� �������� ���������� � �����
class Track : public Media { // ������������ �� Media
private:
    std::string title;
public:
    Track() {}
    Track(const std::string& title) : title(title) {}

    std::string getTitle() const {
        return title;
    }

    void setTitle(const std::string& title) {
        this->title = title;
    }

    // ���������� ��������� ==
    bool operator==(const Track& other) const {
        return this->title == other.title;
    }

    // ������������� ������� ��� ������ ���������� � �����
    friend ostream& operator<<(ostream& os, const Track& track) {
        os << track.title;
        return os;
    }

    void playSong() override { // ���������� ����������� �������
        cout << "������ ����: " << title << endl;
    }
};


// ����� ��� �������� ���������
class Playlist : public Media { // ������������ �� Media
protected: // ����������� protected
    std::vector<Track> tracks; // ���������� std::vector ������ �������
    int current_track;
    static int instance_count; // ����������� ����
public:
    Playlist() : current_track(0) {
        instance_count++;
    }

    Playlist(const Playlist& other) : current_track(other.current_track), tracks(other.tracks) {
        instance_count++;
    }

    Playlist& operator=(const Playlist& other) {
        if (this != &other) {
            current_track = other.current_track;
            tracks = other.tracks;
        }
        return *this;
    }

    virtual void playSong() override { // ����������� �������
        if (!tracks.empty()) {
            cout << "������ ������: " << tracks[current_track].getTitle() << endl;
        }
        else {
            cout << "�������� ����." << endl;
        }
    }


    ~Playlist() {
        instance_count--;
    }

    static int getInstanceCount() { // ����������� �����
        return instance_count;
    }

    void viewSongs() {
        for (size_t i = 0; i < tracks.size(); i++) {
            cout << i + 1 << ". " << tracks[i] << endl;
        }
    }

    void addSong(const Track& song) {
        tracks.push_back(song);
    }

    void removeSong(int index) {
        if (index >= 0 && index < tracks.size()) {
            tracks.erase(tracks.begin() + index);
        }
    }

    void getSongByIndex(int index, Track*& song) { // ������� ����� ���������
        if (index >= 0 && index < tracks.size()) {
            song = &tracks[index];
        }
        else {
            song = nullptr;
        }
    }

    void getSongByIndex(int index, Track& song) { // ������� ����� ������
        if (index >= 0 && index < tracks.size()) {
            song = tracks[index];
        }
    }

    int getTotalNumberOfTracks() {
        return tracks.size();
    }

    std::vector<Track>& getTracks() {
        return tracks;
    }

    int getCurrentTrack() {
        return current_track;
    }

    void setCurrentTrack(int current_track) {
        this->current_track = current_track;
    }

    void load_tracks_from_file(const char* filename) {
        std::ifstream file(filename);
        if (!file) {
            // ���� ���� �� ������, ������� ���
            std::ofstream newFile(filename); // ������� ����� ������ ����
            if (!newFile) {
                throw runtime_error("������ �������� �����");
            }
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            Track song;
            song.setTitle(line);
            addSong(song);
        }

        file.close();
    }

    void save_tracks_to_file(const char* filename) {
        std::ofstream file(filename);
        if (!file) {
            throw runtime_error("������ �������� �����");
        }

        for (size_t i = 0; i < tracks.size(); i++) {
            file << tracks[i].getTitle() << '\n'; // ���������� ������ � ����
        }

        file.close();
    }
};

// ����� ����������� �����
class AdvancedPlaylist : public Playlist {
private:
    string name;
public:
    AdvancedPlaylist() : Playlist(), name("MyPlaylist") {} // ����� ������������ �������� ������
    AdvancedPlaylist(const string& name) : Playlist(), name(name) {}
    AdvancedPlaylist(const AdvancedPlaylist& other) : Playlist(other), name(other.name) {}

    AdvancedPlaylist& operator=(const AdvancedPlaylist& other) {
        if (this != &other) {
            Playlist::operator=(other);
            name = other.name;
        }
        return *this;
    }

    void playSong() override { // ��������������� ����������� �������
        if (!tracks.empty()) {
            cout << "������ �� AdvancedPlaylist '" << name << "': " << tracks[current_track].getTitle() << endl;
        }
        else {
            cout << "�������� '" << name << "' ����." << endl;
        }
    }

    void playSpecificSong(int index) {
        if (index >= 0 && index < tracks.size()) {
            cout << "������ ���������� ����: " << tracks[index].getTitle() << endl;
        }
        else {
            cout << "�������� ������ �����." << endl;
        }
    }

    void setName(const string& name) {
        this->name = name;
    }

    string getName() const {
        return name;
    }
};

int Playlist::instance_count = 0; // ������������� ������������ ����

// ����� ��� ������������ �������� ����������
class User {
private:
    Playlist* playlist;
public:
    User(Playlist* playlist) : playlist(playlist) {}
    void addSongToPlaylist(const Track& song) {
        playlist->addSong(song);
    }
    void removeSongFromPlaylist(int index) {
        playlist->removeSong(index);
    }
    void viewPlaylist() {
        playlist->viewSongs();
    }
};


// ����� ��� �������� ���������
class Volume {
private:
    int volume;
public:
    Volume() : volume(50) {}
    void changeVolume(int new_volume) {
        if (new_volume >= 0 && new_volume <= 100) {
            volume = new_volume;
            cout << ("��������� �������� �� %d%%\n", volume);
        }
        else {
            cout << ("�������� ���������\n");
        }
    }
};

// ����� ��� �������� ���������������
class Playback {
private:
    Playlist* playlist;
    int current_track;
public:
    Playback(Playlist* playlist, int current_track) : playlist(playlist), current_track(current_track) {}
    void playSong() {
        playlist->playSong(); // ����� ����������� ������� �� Playback
    }
};

// ����� ��� �������� �����
class Pause {
private:
    Playlist* playlist;
public:
    Pause(Playlist* playlist) : playlist(playlist) {}
    void pauseSong() {
        cout << ("�� �����\n");
    }
};

// ����� ��� �������� �������� � ���������� �����
class Skip {
private:
    Playlist* playlist;
public:
    Skip(Playlist* playlist) : playlist(playlist) {}
    void skipSong() {
        playlist->setCurrentTrack((playlist->getCurrentTrack() + 1) % playlist->getTotalNumberOfTracks());
        Playback playback(playlist, playlist->getCurrentTrack());
        playback.playSong();
    }
};

// ����� ��� �������� �������� � ����������� �����
class Previous {
private:
    Playlist* playlist;
public:
    Previous(Playlist* playlist) : playlist(playlist) {}
    void previousSong() {
        playlist->setCurrentTrack((playlist->getCurrentTrack() - 1 + playlist->getTotalNumberOfTracks()) % playlist->getTotalNumberOfTracks());
        Playback playback(playlist, playlist->getCurrentTrack());
        playback.playSong();
    }
};

// ����� ��� �������� ��������� ������ � ���������
class View {
private:
    Playlist* playlist;
public:
    View(Playlist* playlist) : playlist(playlist) {}
    void viewSongs() {
        if (playlist->getTotalNumberOfTracks() == 0) {
            cout << "��� ������ � ���������\n";
            return;
        }
        cout << "������ ������:\n";
        for (int i = 0; i < playlist->getTotalNumberOfTracks(); i++) {
            cout << i + 1 << ". " << playlist->getTracks()[i].getTitle() << endl;
        }
    }
};