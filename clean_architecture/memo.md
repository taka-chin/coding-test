クラス図

```mermaid
classDiagram

class User{
    +int id
    +string name
}

class UserInfo{
    +User user
    +string email
    +string phone
}

UserInfo *-- User

```
