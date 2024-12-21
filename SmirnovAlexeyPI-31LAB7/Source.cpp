#include "Header.h"

int main() {
    system("chcp 1251");
    setlocale(LC_ALL, "RUS");

    AdvancedPlaylist playlist("My Favorite Songs"); // ������� ������ ������������ ������ � ������ ���������
    User user(&playlist);
    Volume volume;

    playlist.load_tracks_from_file("playlist.txt");

    int choice;
    while (1) {
        cout << ("���� ������:\n");
        cout << ("0. �������� ����\n");
        cout << ("1. �������� ���������\n");
        cout << ("2. �������������\n");
        cout << ("3. �����\n");
        cout << ("4. ��������� ����\n");
        cout << ("5. ���������� ����\n");
        cout << ("6. ������� ����\n");
        cout << ("7. ����������� ����� � ���������\n");
        cout << ("8. �����\n");
        cout << ("9. ������������� ��������\n");
        cout << ("10. ������������� ���������� ����\n");
        cout << ("��������: ");
        scanf("%d", &choice);

        switch (choice) {
        case 0: {
            Track song;
            cout << "������� �������� �����: ";
            std::string title;
            std::getline(cin >> std::ws, title); // ������ ������ � ��������� �����
            song.setTitle(title);
            user.addSongToPlaylist(song);
            playlist.save_tracks_to_file("playlist.txt");
            break;
        }
        case 1: {
            int new_volume;
            cout << ("������� ��������� (0-100): ");
            scanf("%d", &new_volume);
            volume.changeVolume(new_volume);
            break;
        }
        case 2: {
            if (playlist.getTotalNumberOfTracks() > 0) {
                playlist.playSong(); // ����� ���������������� ����������� �������
            }
            else {
                cout << "��� ������ � ���������\n";
            }
            break;
        }
        case 3:
            if (playlist.getTotalNumberOfTracks() > 0) {
                Pause pause(&playlist);
                pause.pauseSong();
            }
            else {
                cout << ("��� ������ � ���������\n");
            }
            break;
        case 4:
            if (playlist.getTotalNumberOfTracks() > 0) {
                Skip skip(&playlist);
                skip.skipSong();
            }
            else {
                cout << "��� ������ � ���������\n";
            }
            break;
        case 5:
            if (playlist.getTotalNumberOfTracks() > 0) {
                Previous previous(&playlist);
                previous.previousSong();
            }
            else {
                cout << ("��� ������ � ���������\n");
            }
            break;
        case 6: {
            if (playlist.getTotalNumberOfTracks() > 0) {
                int index;
                cout << ("������� ������ ����� ��� ��������: ");
                scanf("%d", &index);
                if (index >= 1 && index <= playlist.getTotalNumberOfTracks()) {
                    playlist.removeSong(index - 1);
                    playlist.save_tracks_to_file("playlist.txt"); // ��������� ��������� � �����
                }
                else {
                    cout << ("�������� ������\n");
                }
            }
            else {
                cout << ("��� ������ � ���������\n");
            }
            break;
        }
        case 7: {
            View view(&playlist);
            view.viewSongs();
            break;
        }
        case 8:
            return 0;
        case 9: {
            string newName;
            cout << "������� ����� ��� ���������: ";
            cin >> ws;
            getline(cin, newName);
            playlist.setName(newName);
            cout << "��� ��������� �������� ��: " << playlist.getName() << endl;
            break;
        }
        case 10: {
            int index;
            cout << "������� ������ ����� ��� ���������������: ";
            cin >> index;
            playlist.playSpecificSong(index - 1);
            break;
        }
        default:
            cout << "������ ������ ��������\n";
        }
        cout << ("\n\n");
    }

    // ������ ������������� ������������
    Playlist* basePlaylist = new AdvancedPlaylist();
    basePlaylist->addSong(Track("BaseTrack"));
    basePlaylist->playSong(); // ����� ����������� ������� ����� ��������� �� ������� �����

    AdvancedPlaylist* advancedPlaylist = dynamic_cast<AdvancedPlaylist*>(basePlaylist);

    if (advancedPlaylist) {
        advancedPlaylist->playSpecificSong(0);
    }

    delete basePlaylist;

    return 0;
}