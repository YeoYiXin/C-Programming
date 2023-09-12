# C-Programming
 Projects done with C 
1. Only projects written in C but with .cpp extensions is worked on using C-Free Standard. The other projects are coded with VS Code<br/>
<br/>
<b>Theme-Park-Booking-System</b><br/>
 This is a program which books tickets for a theme park (a booking system). The theme park has only 40 persons capacity. The visitors may be local and international. <br/><br/>
 The program can perform following tasks:<br/>
 1. Add a new visitor information which must have the following:<br/>
 (Sr No., Full Name, ID (IC or passport), Ticket No)<br/>
 2. Search visitor information based on Ticket No, Name, or ID<br/>
 3. Delete the visitor information based on ticket number<br/>
 4. Delete the visitor information based on full name<br/>
 5. Delete the visitor information based on ID<br/>
 6. Display Total No of tickets sold<br/>
<br/>
For local visitors the booking system should record the following<br/>
Sr_No. Ticket_number full_name ID (local)<br/><br/>
For international visitors the following information should be collected.<br/>
Sr_No. Ticket_number full_name ID (International)<br/><br/>
The booking system should generate an output file “Tickets.txt”<br/><br/>

Extra information: <br/>
1. The search operation should match the name regardless of the capitalization or small alphabets.
For example; if someone search “yeo yi xin” or “yeo Yi XiN” or “YEO YI XIN” the search
function should provide the information of “Yeo_Yi_Xin”, meaning both should be considered
same.<br/>
NOTE: If more than one visitors have same name then it should display all the visitors with the
same name. <br/>
2.  If any visitor’s information is deleted based on ticket no, name, or ID, the Ticket.txt file should
be updated so that it preserve the modified visitor’s information. In case of same
multiple visitors with same name, visitor’s information is deleted based on ID. Visitor's serial number is not changed.<br/>
3. If the total number of visitor’s information is asked, the Tickets.txt file should provide the
complete list of visitors.

