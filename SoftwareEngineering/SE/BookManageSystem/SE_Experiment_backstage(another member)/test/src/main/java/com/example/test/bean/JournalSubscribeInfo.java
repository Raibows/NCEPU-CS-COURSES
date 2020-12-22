package com.example.test.bean;

public class JournalSubscribeInfo {

    private int id;
    private String journalNo;
    private String stuId;
    private String period;
    private String journalName;
    private String description;

    public int getId() {
        return id;
    }

    public String getJournalNo() {
        return journalNo;
    }

    public String getStuId() {
        return stuId;
    }

    public void setId(int id) {
        this.id = id;
    }

    public void setJournalNo(String journalNo) {
        this.journalNo = journalNo;
    }

    public void setStuId(String stuId) {
        this.stuId = stuId;
    }

    public String getPeriod() {
        return period;
    }

    public String getJournalName() {
        return journalName;
    }

    public String getDescription() {
        return description;
    }

    public void setPeriod(String period) {
        this.period = period;
    }

    public void setJournalName(String journalName) {
        this.journalName = journalName;
    }

    public void setDescription(String description) {
        this.description = description;
    }

}
