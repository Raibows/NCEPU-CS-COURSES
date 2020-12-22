package com.example.backstage.Entity.MaintainEntity;

import lombok.Data;
import lombok.Getter;
import lombok.Setter;

import javax.persistence.*;

@Entity
@Table(name = "publisher")
@Data
public class Publisher {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;
    private String publisherName;
    private String publisherAddr;
    private String phoneNumber;

    public Publisher(String publisherName, String publisherAddr, String phoneNumber) {
        this.publisherName = publisherName;
        this.publisherAddr = publisherAddr;
        this.phoneNumber = phoneNumber;
    }

    public Publisher() {
    }
}
