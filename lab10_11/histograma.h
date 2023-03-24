#pragma once
#include "qwidget.h"
#include "qpainter.h"

class Histograma : public QWidget {
private:
	SrvLocatari& srv;

public:

	Histograma(SrvLocatari& srv) :srv{ srv }{};

	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		p.drawLine(0, 0, width(), height());

	}

};