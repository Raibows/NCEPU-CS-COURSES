package com.example.backstage.Entity.MaintainEntity;

import lombok.Data;
import lombok.Getter;
import lombok.Setter;
import org.hibernate.annotations.GeneratorType;
import org.hibernate.annotations.GenericGenerator;

import javax.persistence.*;

@Data
@Table(name = "user")
@Entity
public class User {
       @Id
       private String id;
       private String name;
       private String sex;
       private String major;
       private String uclass;
       private String borrowid;
       @Column(name = "borrowNum")
       private int borrowNum;
       private String pwd;
       private int role;
       private int penalty;

    public User(String id, String name, String sex, String major, String uclass, String borrowid, int borrowNum, String pwd, int role,int penalty) {
        this.id = id;
        this.name = name;
        this.sex = sex;
        this.major = major;
        this.uclass = uclass;
        this.borrowid = borrowid;
        this.borrowNum = borrowNum;
        this.pwd = pwd;
        this.role = role;
        this.penalty=penalty;
    }

    public User() {
    }
}
