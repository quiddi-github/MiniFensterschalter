# MiniFensterschalter

Stand 7.7.2019

Software für eine Fenstersteuerung

Hardware:
Eingang auf Pin 5 & Pin 6;
Ausgang auf Pin 11 & Pin 12;
Eingang 5 schaltet Ausgang 11 und Eingang 6 schaltet Ausgang 12;

Schaltung kann Tippbetrieb und Tastenbetrieb. Tippbetrieb ist aktiv sofern der Taster kürzer als TasterZeit gedrückt wurde, jedoch die Entprellungszeit überschritten ist. Der Tippbetrieb ist dann für DauerAnZeit aktiv. Wird eine Taste während des Tippbetriebes gedrückt, ist dieser sofort deaktiviert. Ist die Taste länger als TasterZeit gedrückt, so wird der Ausgang sofort abgeschalten beim Loslassen des Tasters.

Die Konstanten befinden sich im Code ganz am Anfang.

Änderung vom 7.7.2019: Relais sind LOW-Active, Anpassung des Codes.
