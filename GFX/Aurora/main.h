void loop() {
    pattern.drawFrame();
    matrix->show();
}

void setup() {
    delay(1000);
    Serial.begin(115200);

    matrix_setup();
    Serial.print("Matrix Size: ");
    Serial.print(mw);
    Serial.print(" ");
    Serial.println(mh);
    matrix->begin();
    matrix->setBrightness(matrix_brightness);
    matrix->setTextWrap(false);

    effects.leds = matrixleds;
    effects.Setup();
    pattern.start();
    matrix->clear();
}

// vim:sts=4:sw=4
