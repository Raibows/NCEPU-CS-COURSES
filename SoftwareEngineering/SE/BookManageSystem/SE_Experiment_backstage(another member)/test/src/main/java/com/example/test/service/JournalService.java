package com.example.test.service;

import com.example.test.bean.JournalBean;
import com.example.test.bean.JournalSubscribeInfo;

import java.util.List;

public interface JournalService {

    List<JournalBean> SearchJournal(String period);
    boolean AddJournal(String no,String journalName,String startYear,String period,String description);
    boolean DeleteJournal(String no);
    boolean ModifyJournal(String no,String description,String period);
    boolean JournalSubscibe(String journalNo,String stuId,String journalName,String period,String description);
    boolean JournalCancel(String journalNo,String stuId);
    List<JournalSubscribeInfo> SearchSubscribe(String stuId );

}
