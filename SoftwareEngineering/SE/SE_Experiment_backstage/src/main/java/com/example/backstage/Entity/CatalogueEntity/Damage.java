package com.example.backstage.Entity.CatalogueEntity;

import lombok.Data;

import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;
import java.math.BigDecimal;

@Entity
@Data
@Table(name = "damage_list")
public class Damage {
    @Id
    private String isbn;
    private String bookName;
    private String reason;
    private BigDecimal price;
    private boolean state;
    private String checker;

    public Damage(String isbn, String bookName, String reason, BigDecimal price, boolean state, String checker) {
        this.isbn = isbn;
        this.bookName = bookName;
        this.reason = reason;
        this.price = price;
        this.state = state;
        this.checker = checker;
    }

    public Damage() {
    }
}
