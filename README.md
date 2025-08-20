## 🎟️ **E-Ticket Booking System – UML Structure**

### 🔹 Class: **Passenger**

* **Private Attributes**

  * `string name`
  * `int age`
  * `string contact`
* **Public Methods**

  * `Passenger(...)` → constructor(s)
  * `getName()`, `getAge()`, `getContact()`
  * `displayPassenger()`
* **Friend**

  * `friend class SecurityCheck;`

---

### 🔹 Abstract Class: **Ticket** *(Base Class)*

* **Protected Attributes**

  * `int ticketID`
  * `double baseFare`
  * `Passenger passenger`
* **Public Methods**

  * `Ticket(...)` → constructor(s)
  * `virtual double calculateFare() = 0;` *(pure virtual)*
  * `virtual void displayTicket();`
  * `operator<<` (overloaded for output)

---

### 🔹 Derived Classes (Inheritance + Polymorphism)

1. **BusTicket : public Ticket**

   * Extra Attributes: `string route`, `double distance`
   * Overrides `calculateFare()`

2. **TrainTicket : public Ticket**

   * Extra Attributes: `string classType`
   * Overrides `calculateFare()`

3. **MovieTicket : public Ticket**

   * Extra Attributes: `string seatType`
   * Overrides `calculateFare()`

---

### 🔹 Diamond Problem Demonstration

* **Transport (Base)**

  * `string transportID`
* **Bus : virtual public Transport**
* **Train : virtual public Transport**
* **LuxuryBusTrain : public Bus, public Train**

  * Solves diamond problem using *virtual inheritance*

---

### 🔹 Class: **BookingSystem**

* **Static Attributes**

  * `static int totalTicketsSold`
* **Public Methods**

  * `bookTicket(Ticket* t)`
  * `saveBookingToFile(Ticket* t)`
  * `showAllBookings()`
* **Template Function**

  * `template<class T> searchTicket(T key)`

---

### 🔹 Class: **SecurityCheck** *(Friend Class)*

* **Methods**

  * `verifyPassenger(Passenger p)` → Access private passenger details

---

### 🔹 Exception Handling

* Custom Exception Class: `InvalidBookingException`
* Used when:

  * Passenger age < 0
  * Invalid ticket type
  * File not found

---

## 🔹 Relationships (UML Style)

* **Passenger → Ticket** (Composition: a ticket *has-a* passenger).
* **Ticket → BusTicket / TrainTicket / MovieTicket** (Inheritance).
* **Transport → Bus & Train → LuxuryBusTrain** (Diamond problem, solved with virtual).
* **BookingSystem → Ticket** (Association: BookingSystem *uses* Ticket).
* **SecurityCheck ↔ Passenger** (Friendship).

---

✅ This structure **covers everything** your teacher asked:

* Encapsulation ✔
* Inheritance (including Diamond Problem) ✔
* Polymorphism (overloading + overriding) ✔
* Abstraction ✔
* Static members ✔
* File handling ✔
* Exception handling ✔
* Friend class ✔
* Templates ✔
* Constructors/Destructors naturally included ✔

---