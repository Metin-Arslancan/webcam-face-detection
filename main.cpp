#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main() {
    
    CascadeClassifier detector;

    if (!detector.load(
        "/home/metin/CLionProjects/BVA_test/haarcascade_frontalface_default.xml")) {
        cout << "Modell konnte nicht geladen werden!" << endl;
        return 1;
    }

    VideoCapture kamera(0);

    if (!kamera.isOpened()) {
        cout << "Webcam konnte nicht geöffnet werden!" << endl;
        return 1;
    }

    // Webcam-Auflösung reduzieren
    kamera.set(CAP_PROP_FRAME_WIDTH, 640);
    kamera.set(CAP_PROP_FRAME_HEIGHT, 480);

    Mat bild, grau, klein;
    vector<Rect> gesichter;

    while (true) {

        kamera >> bild;

        if (bild.empty()) {
            break;
        }

        cvtColor(bild, grau, COLOR_BGR2GRAY);
        resize(grau, klein, Size(), 0.5, 0.5);
        equalizeHist(klein, klein);
        gesichter.clear();

        detector.detectMultiScale(
            klein,
            gesichter,
            1.1,
            5,
            0,
            Size(30, 30)
        );

        // Erkannte Gesichter markieren
        for (const auto& gesicht : gesichter) {

            Rect original(
                gesicht.x * 2,
                gesicht.y * 2,
                gesicht.width * 2,
                gesicht.height * 2
            );

            rectangle(
                bild,
                original,
                Scalar(0, 255, 0),
                2
            );
        }

        // Anzahl erkannter Gesichter anzeigen
        putText(
            bild,
            "Gesichter: " + to_string(gesichter.size()),
            Point(20, 40),
            FONT_HERSHEY_SIMPLEX,
            0.8,
            Scalar(0, 255, 0),
            2
        );

        imshow("Live-Gesichtserkennung", bild);
        if (waitKey(1) == 27) {
            break;
        }
    }

    kamera.release();
    destroyAllWindows();

    return 0;
}