package com.example.backstage.Entity.InterviewEntity;

import com.example.backstage.Entity.MaintainEntity.User;
import com.fasterxml.jackson.annotation.JsonFormat;
import lombok.Data;
import lombok.Getter;
import lombok.Setter;

import javax.persistence.*;
import java.math.BigDecimal;
import java.util.Date;

@Entity
@Data
@Table(name = "interviewlist")
public class Interview {
    @Id
    private String id;
    private String userId;
    private String bookSeller;
    private BigDecimal price;

    public Interview(String id, String userId, String bookSeller, BigDecimal price, Date orderDate, String isbn, String bookName, int num, String name) {
        this.id = id;
        this.userId = userId;
        this.bookSeller = bookSeller;
        this.price = price;
        this.orderDate = orderDate;
        this.isbn = isbn;
        this.bookName = bookName;
        this.num = num;
        this.name = name;
    }

    @JsonFormat(pattern = "yyyy-MM-dd")
    private Date orderDate;
    private String isbn;
    private String bookName;
    private int num;
    private String name;


    public Interview() {
    }
}
