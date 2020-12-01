package com.example.backstage.Entity.CatalogueEntity;

import lombok.Data;

import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;

@Entity
@Data
@Table(name = "temporary_entry")
public class Temporary {
    @Id
    private String isbn;
    private String bookName;
    private boolean hasEntry;
    private String opName;


    public Temporary(String isbn, String bookName, boolean hasEntry, String opName) {
        this.isbn = isbn;
        this.bookName = bookName;
        this.hasEntry = hasEntry;
        this.opName = opName;
    }

    public Temporary() {
    }
}
