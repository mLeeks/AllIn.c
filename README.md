
## Projektidee
---
>AllIn.c ist ein konsolenbasiertes Pokerprogramm, das in der Programmiersprache C entwickelt wird. Nutzende können Texas Hold’em gegen eine selbst gewählte Anzahl computergesteuerter Gegner spielen.

>Das Programm soll die offiziellen Spielregeln von Texas Hold’em umsetzen, einschließlich Setzrunden, Blinds, Handbewertung und Gewinnerermittlung.

>Als optionale Erweiterung ist eine Client-Server-Architektur vorgesehen, die Multiplayer-Partien gegen menschliche Mitspielende ermöglicht.

## Anforderungen
---
### A-01: Texas Hold’em Regelwerk umsetzen
**Ziel**: Das Spiel wird Texas Hold’em Regelwerk konform implementiert.
**Akteur**: Programmierer
**Regelreferenz**: [[TDA Regeln 2026 Deutsche Version 1.0.pdf]]
**Haupt-RegelReferenz**: https://de.wikipedia.org/wiki/Texas_Hold%E2%80%99em

### A-02: Neues Spiel konfigurieren
**Ziel**: Der Nutzende erhält beim Starten des Programms ein Hauptmenü. Darüber können Einstellungen, wie

| Variable             | Datentyp      | Standardwert          | Priorität |
| -------------------- | ------------- | --------------------- | --------- |
| Gegner-Anzahl        | Integer (1-9) | 3                     | Pflicht   |
| Big Blind            | Integer       | 200                   | Pflicht   |
| Small Blind          | Integer       | 100 (Big Blind / 2)   | Pflicht   |
| Startkapital         | Integer       | 2000 (10 * Big Blind) | Pflicht   |
| Debug_Mode           | Boolean       | false                 | Pflicht   |
| Bot Schwierigkeit    | Enum          | Normal                | Optional  |
| Spielgeschwindigkeit | Integer       | 1000                  | Optional  |
getätigt werden.

> **Zusätzlich sieht der Nutzende sein eigenes Kapital.**



---
## Spielrollen
- Dealer-Button
    - ist ein Spieler und wandert nach jeder Hand im Uhrzeigersinn
- Kartengeber
- Small Blind
    - Halber Wert d. Big Blinds
    - Initial: links vom Dealer
- Big Blind
    - doppelter Wert d. Small Blinds
    - Initial: Links vom Small Blind
- KI
- Spieler
    - müssen keinen Grundeinsatz (**ante**) leisten

## Ablaufsplanung

### Hand (Runde)
#### Hand-Ende
- alle Spieler - bis auf einen (erhält Pot) - steigen aus
- Mehr als Ein Spieler am Tisch und alle haben gecalled
    - Kartenwerte entscheiden
#### Wettrunden + organisatorische
1. Pre-Flop
    - Jeder Spieler: Starthand (2 Karten)
    - Startspieler: Links vom Big Blind (eröffnet erste Wettrunde)
    -  **Spieleroptionen:
        - Call
        - Raise
        - Fold
2. Flop
    - Kartengeber legt
        - erste Karte verdeckt neben Stapel (Burn Card)
        - drei Karten offen auf den Tisch (Flop)
    - Spieler in **First position** (Spieler links vom Geber) spricht in allen Wettrunden als Erster
    -  **Spieleroptionen:
        - Call
        - Raise
        - Fold
        - Check
        - Bet
    - **Spieleroptionen (sobald ein Spieler ein Bet setzt)**
        - Call
        - Raise
        - Fold
    - Die Wettrunde wird solange fortgesetzt bis
        - alle Spieler den Einsatz gehalten haben
        - oder alle, bis auf einer, aus dem Spiel ausgestiegen sind
3. Turn
    - Kartengeber legt
        - Karte verdeckt vom Stapel
        - eine vierte offene Karte (Turn Card)
    - Wenn Spread Limit --> Higher Limit gilt jetzt
    - Rest analog zur Vorrunde
4. River
    - Kartengeber legt
        - Karte verdeckt vom Stapel
        - fünfte offene Karte (River Card)
    - Rest analog zur Vorrunde
5. Showdown
    - Findet nach der letzten Wettrunde statt
    - Spieler der seine Hand (Kombination) vollständig zeigen muss:
        - in der letzten Wettrunde als letzter erhöht _(raise)_ oder
        - falls niemand erhöht hat, derjenige, der in der letzten Wettrunde als erster gesetzt _(bet)_ hat, oder
        - falls niemand gesetzt hat, derjenige, der sich in _First position_ befindet
    - Nachfolgende Spieler können Gewinnberechtigung nachweisen und ihre Karten aufdecken (müssen aber nicht)
    - Pot verteilung
        - Spieler mit höchster Hand (Kombination) gewinnt Pot
        - Bei gleichwertigen Kombinationen wird der Pot aufgeteilt (Split pot)
        - Nicht teilbare Jeton
            - geht an den Spieler der am nähesten Links vom Dealer-Button sitzt

> - Nach Abschluss der Hand wandert der Dealer-Button im Uhrzeigersinn zum nächsten Spieler
> - Nachkaufen von Chips ist erlaubt
> 	- Buy-In Obergrenze darf nicht überschritten werden
> - No-Ratholing-Regel
> 	- Teilbeträge dürfen nicht vom Tisch genommen werden
> 	- wenn, muss der Tisch verlassen werden **(Für das Spiel maybe verbieten?)**

## Sonderregeln
### Heads-Up (nur noch zwei Spieler)
- **Dealer** = immer Small Blind
- **Anderer Spieler** = immer Big Blind
- Nach jeder Hand wechselt der Dealer-Button zum anderen Spieler. Damit tauschen die beiden auch ihre Blinds.

### Wettrunden Raising
- Ein Spieler darf in einer Wettrunde **nicht zweimal in Folge** raisen
    - nur wenn ein anderer dazwischen auch raised

## Limits
### Not Limit (NLHE)
### Pot Limit (PLHE)
### Split Limit (auch: Spread Limit)
### Fixed Limit (LHE)

## Abgrenzungen
- Time Collection bzw. Taxe nicht berücksichtigt
- Side-Pots werden **vorerst** nicht implementiert
    - der Spieler mit dem geringsten All-in bestimmt Grenze d. Pots


## Kombinationen
| Name                                  | Bedeutung                                                                                                              | Beispiel              | Entscheidungskriterium                |
| ------------------------------------- | ---------------------------------------------------------------------------------------------------------------------- | --------------------- | ------------------------------------- |
| **Höchste Karte**  <br>(_High Card_)  | Keine der unteren Kombinationen                                                                                        | A♠  <br>K♦ J♠ 7♣ 4♣   | Höhe der einzelnen Karten             |
| **Ein Paar**  <br>(_One Pair_)        | Zwei Karten gleichen Wertes                                                                                            | 10♠ 10♥  <br>J♦ 8♣ 6♥ | Höhe des Paars und der Beikarten      |
| **Zwei Paare**  <br>(_Two Pair_)      | Zwei Paare                                                                                                             | J♦ J♠ 8♣ 8♠  <br>A♠   | Höhe der Paare und der Beikarte       |
| **Drilling**  <br>(_Three of a Kind_) | Drei Karten gleichen Wertes                                                                                            | Q♣ Q♥ Q♠  <br>A♥ 4♣   | Höhe des Drillings und der Beikarten  |
| **Straße**  <br>(_Straight_)          | Fünf Karten in einer Reihe                                                                                             | 7♥ 8♣ 9♦ 10♥ J♠       | Höchste Karte                         |
| **Flush**                             | Fünf Karten in einer Farbe                                                                                             | 3♠ 5♠ 8♠ 9♠ K♠        | Höhe der einzelnen Karten             |
| **Full House**                        | Ein Drilling und ein Paar                                                                                              | K♥ K♣ K♦ 9♠ 9♦        | Höhe des Drillings und Höhe des Paars |
| **Vierling**  <br>(_Four of a Kind_)  | Vier Karten gleichen Wertes                                                                                            | A♣ A♦ A♥ A♠  <br>4♠   | Höhe des Vierlings und der Beikarte   |
| **Straight Flush**                    | Straße in einer Farbe                                                                                                  | 8♣ 9♣ 10♣ J♣ Q♣       | Höchste Karte                         |
| **Royal Flush**                       | Straße in einer Farbe mit [Ass](https://de.wikipedia.org/wiki/Ass_\(Spielkarte\) "Ass (Spielkarte)") als höchste Karte | 10♦ J♦ Q♦ K♦ A♦       | Split Pot                             |
## Architektur und Core-Ablauf
[Architektur](./architektur.drawio.svg)
## Datenmodelle
[Datenmodelle](./datenmodelle.drawio.svg)
## Entwicklungsreihenfolge
1. Core
    1. Cards
    2. Player
    3. Game
    4. Betting
    5. HandEvaluator
    6. PotManager
    7. GameView
2. Player
3. KI
4. Netzwerk