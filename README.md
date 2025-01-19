# Trading Order Book Simulation

A C++ project that simulates a basic order book system, a critical component in financial trading platforms. This application allows users to add buy and sell orders, matches them based on predefined rules, and displays the current state of the order book.

## Table of Contents
- [About the Project](#about-the-project)
- [Features](#features)
- [Technologies Used](#technologies-used)
- [Getting Started](#getting-started)
- [How It Works](#how-it-works)
- [Future Improvements](#future-improvements)

---

## About the Project
This project implements a simplified **order matching system** commonly used in stock exchanges and trading platforms. The goal is to demonstrate skills in:
- Data structures and algorithms.
- Object-oriented programming.
- Efficient implementation of core trading concepts like order matching and priority handling.

**Key Objective:** Buyers and sellers can place orders, and the system will automatically match them based on price and time priority.

---

## Features
- **Order Matching**: Matches buy and sell orders based on:
  - Highest buy price meets or exceeds lowest sell price.
  - Time priority for orders at the same price.
- **Dynamic Order Book**:
  - Maintains two order books: Buy (max-heap) and Sell (min-heap).
  - Updates in real-time as orders are matched or added.
- **Interactive Console Interface**:
  - Add orders via user input.
  - View the current state of buy and sell orders.

---

## Technologies Used
- **C++**: Core programming language.
- **Priority Queues**: Used for efficient order matching.
- **OOP Principles**: Encapsulated logic within `Order` and `OrderBook` classes.

