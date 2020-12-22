package com.example.backstage.Entity.InterviewEntity;

import com.fasterxml.jackson.annotation.JsonFormat;
import lombok.Data;

import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;
import java.math.BigDecimal;
import java.util.Date;

@Entity
@Data
@Table(name = "refund")
public class Refund {
    @Id
    private String isbn;
    private String userId;
    @JsonFormat(pattern = "yyyy-MM-dd")
    private Date orderDate;
    private BigDecimal price;
    private String reason;
    private int num;

    public Refund(String isbn, String userId, Date orderDate, BigDecimal price, String reason, int num, boolean state, String name) {
        this.isbn = isbn;
        this.userId = userId;
        this.orderDate = orderDate;
        this.price = price;
        this.reason = reason;
        this.num = num;
        this.state = state;
        this.name = name;
    }

    private boolean state;
    private String name;

    public Refund() {
    }
}
