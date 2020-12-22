package com.example.test.bean;

import com.fasterxml.jackson.annotation.JsonAutoDetect;
import com.fasterxml.jackson.annotation.JsonFormat;
import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Getter;
import lombok.Setter;
import org.springframework.format.annotation.DateTimeFormat;

import java.util.Date;



public class BorrowInfo {


    private int id;
    private String stuid;
    private String isbn;
    @DateTimeFormat(pattern="yyyy-MM-dd")
    @JsonFormat(
            pattern = "yyyy-MM-dd"
    )
    private Date borrowDate;
    @DateTimeFormat(pattern="yyyy-MM-dd")
    @JsonFormat(
            pattern = "yyyy-MM-dd"
    )
    private Date returnDate;
    private int borrowPeriod;
    private String bookName;
    private int status;

    public String getBookName() {
        return bookName;
    }

    public void setBookName(String bookName) {
        this.bookName = bookName;
    }

    public int getId() {
        return id;
    }

    public String getStuid() {
        return stuid;
    }

    public String getIsbn() {
        return this.isbn;
    }

    public void setStuid(String stuid) {
        this.stuid = stuid;
    }

    public void setIsbn(String isbn) {
        this.isbn = isbn;
    }

    public Date getBorrowDate() {
        return borrowDate;
    }

    public Date getReturnDate() {
        return returnDate;
    }

    public int getBorrowPeriod() {
        return borrowPeriod;
    }

    public int getStatus() {
        return status;
    }

    public void setId(int id) {
        this.id = id;
    }



    public void setBorrowDate(Date borrowDate) {
        this.borrowDate = borrowDate;
    }

    public void setReturnDate(Date returnDate) {
        this.returnDate = returnDate;
    }

    public void setBorrowPeriod(int borrowPeriod) {
        this.borrowPeriod = borrowPeriod;
    }

    public void setStatus(int status) {
        this.status = status;
    }
}
