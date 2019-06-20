# MiniFensterschalter

Stand 20.6.2019

Software fr eine Fenstersteuerung

Hardware
Eingang auf Pin 5 & Pin 6
Ausgang Auf Pin 11 & Pin 12
Eingang 5 schaltet Ausgang 11 und Eingang 6 schaltet Ausgang 12

Schaltung kann Tippbetrieb und Tastenbetrieb. Tippbetrieb ist aktiv sofern der Taster krzer als TasterZeit gedrckt wurde, jedoch die Entprellungszeit berschritten ist. Der Tippbetrieb ist dann fr DauerAnZeit aktiv. Wird eine Taste whrend des Tippbetriebes gedrckt ist dieser sofort deaktiviert. Ist die Taste lnger als TasterZeit gedrckt, so wird der Ausgang sofort abgeschalten bei loslassen des Tasters.
