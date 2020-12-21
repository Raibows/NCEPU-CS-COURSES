package com.example.backstage.Entity.MaintainEntity;

import lombok.Data;
import lombok.Getter;
import lombok.Setter;
import org.springframework.format.annotation.DateTimeFormat;

import javax.persistence.*;
import java.util.Date;

@Data
@Table(name = "bookinfo")
@Entity
public class Book {
    @Id
    private String isbn;
    private String bookName;
    private int type;
    private String author;
    private boolean canBorrow;
    private String publisher;
    private String publishDate;
    private int num;
    private String url;

    public Book(String isbn, String bookName, int type, String author, boolean canBorrow, String publisher, String publishDate, int num, String url) {
        this.isbn = isbn;
        this.bookName = bookName;
        this.type = type;
        this.author = author;
        this.canBorrow = canBorrow;
        this.publisher = publisher;
        this.publishDate = publishDate;
        this.num = num;
        this.url = url;
    }

    public Book() {
    }
}
