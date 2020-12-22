package com.example.backstage.Entity.CatalogueEntity;

import lombok.Data;

import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;
import java.util.Date;

@Entity
@Data
@Table(name = "alumnus_donation")
public class Donation {
    @Id
    private String id;
    private String stuId;
    private String name;
    private String major;
    private String bookName;
    private Date donateDate;
    private int num;
    private String isbn;



    public Donation() {
    }
}
