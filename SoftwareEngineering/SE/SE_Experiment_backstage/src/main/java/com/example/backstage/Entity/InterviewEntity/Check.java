package com.example.backstage.Entity.InterviewEntity;

import lombok.Data;
import lombok.Getter;
import lombok.Setter;

import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;

@Entity
@Data
@Table(name = "checklist")
public class Check {
    @Id
    private String id;
    private String bookSeller;
    private String userId;
    private String bookName;
    private String isbn;
    private int num;
    private String name;

    public Check(String id, String bookSeller, String userId, String bookName, String isbn, int num, String name) {
        this.id = id;
        this.bookSeller = bookSeller;
        this.userId = userId;
        this.bookName = bookName;
        this.isbn = isbn;
        this.num = num;
        this.name = name;
    }

    public Check() {
    }
}
