package com.example.test.bean;

import java.util.Date;

public class CirculatingLibrary {

    private String ISBN;
    private String BookName;
    private int Type;
    private String Author;
    private int CanBorrow;
    private String Publisher;
    private Date PublishDate;

    public String getISBN() {
        return ISBN;
    }

    public String getBookName() {
        return BookName;
    }

    public int getType() {
        return Type;
    }

    public String getAuthor() {
        return Author;
    }

    public int getCanBorrow() {
        return CanBorrow;
    }

    public String getPublisher() {
        return Publisher;
    }

    public Date getPublishDate() {
        return PublishDate;
    }

    public void setISBN(String ISBN) {
        this.ISBN = ISBN;
    }

    public void setBookName(String bookName) {
        BookName = bookName;
    }

    public void setType(int type) {
        Type = type;
    }

    public void setAuthor(String author) {
        Author = author;
    }

    public void setCanBorrow(int canBorrow) {
        CanBorrow = canBorrow;
    }

    public void setPublisher(String publisher) {
        Publisher = publisher;
    }

    public void setPublishDate(Date publishDate) {
        PublishDate = publishDate;
    }
}
